#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Kernel.h"


////////////////////////////////
__global__ void calc_norms(
	Point *dev_points,
	const Centroid *const dev_centroids,
	const int centroids_size,
	const int vector_size)
{
	int block_size = blockDim.x;
	double temp_norm;

	if (!dev_points[blockIdx.x*block_size + threadIdx.x].isDummyPoint)
	{
		Point* point = &dev_points[blockIdx.x*block_size + threadIdx.x];

		//init first norm
		temp_norm = 0;
		for (int i = 0; i<vector_size; i++) {
			temp_norm += pow((point->vector[i]) - (dev_centroids[0].vector[i]), 2);
		}
		temp_norm = sqrt(temp_norm);
		point->minDis = temp_norm;
		point->myCentroidIndex = 0;

		//do the rest
		for (int i = 1; i<centroids_size; i++)
		{
			temp_norm = 0;
			for (int j = 0; j<vector_size; j++) {
				temp_norm += pow((point->vector[j]) - (dev_centroids[i].vector[j]), 2);
			}
			temp_norm = sqrt(temp_norm);

			if (temp_norm < (point->minDis))
			{
				point->minDis = temp_norm;
				point->myCentroidIndex = i;
			}
		}
	}
}
////////////////////////////////

////////////////////////////////
void check_cuda_status(const cudaError_t *const cudaStatus, const char *const error_msg, const int line_number)
{
	if (*cudaStatus != cudaSuccess)
	{
		printf("%d-%s\n", (line_number - 1), error_msg);
		printf("%s\n", cudaGetErrorString(*cudaStatus));
		system("PAUSE");
		exit(1);
	}
}

int get_max_num_of_threads_per_block()
{
	struct cudaDeviceProp properties;
	cudaGetDeviceProperties(&properties, 0);
	return properties.maxThreadsPerBlock;
}

/*
* adds dummy-points that will not be taken into considoration
* when doing calculations.
* the dummy-points are added to match the max number of threads and blocks when a kernel lunch is made.
*/
void set_points_to_work_with_cuda(Point **points_ptr, int *points_size_ptr)
{
	int current_points_size = *points_size_ptr;
	int max_thr_per_block = get_max_num_of_threads_per_block();
	int left_points = -1;

	//in case: we dont have an integer number of blocks
	if ((left_points = (*points_size_ptr) % max_thr_per_block) != 0)
	{
		*points_size_ptr = current_points_size + (max_thr_per_block - left_points);
		(*points_ptr) = (Point*)realloc((*points_ptr), sizeof(Point)*(*points_size_ptr));


#pragma omp parallel for default(shared)
		for (int i = current_points_size; i<(*points_size_ptr); i++)
		{
			(*points_ptr)[i].minDis = -1;
			// (*points_ptr)[i].myCentroidIndex = -1;
			(*points_ptr)[i].myCentroidIndex = 101;// set immpossible cluster index for this project def
			(*points_ptr)[i].isDummyPoint = 1;
		}
	}
}

void classify_points_by_norm_alloc(
	Point** dev_points_ptr, const int num_of_points,
	Centroid** dev_centroids_ptr, const int num_of_centroids) {

	static cudaError_t cudaStatus;

	cudaStatus = cudaMalloc((void**)dev_points_ptr, sizeof(Point)*num_of_points);
	check_cuda_status(&cudaStatus, "cudaMalloc failed! :: classify_points_by_norm_alloc", __LINE__);

	cudaStatus = cudaMalloc((void**)dev_centroids_ptr, sizeof(Centroid)*num_of_centroids);
	check_cuda_status(&cudaStatus, "cudaMalloc failed! :: classify_points_by_norm_alloc", __LINE__);

}

void classify_points_by_norm_memCopy(
	Point* points, const int num_of_points,
	Centroid* centroids, const int num_of_centroids,
	Point* dev_points, Centroid* dev_centroids) {

	static cudaError_t cudaStatus;

	cudaStatus = cudaMemcpy(dev_points, points, num_of_points * sizeof(Point), cudaMemcpyHostToDevice);
	check_cuda_status(&cudaStatus, "cudaMemcpy failed! :: classify_points_by_norm_memCopy", __LINE__);

	cudaStatus = cudaMemcpy(dev_centroids, centroids, num_of_centroids * sizeof(Centroid), cudaMemcpyHostToDevice);
	check_cuda_status(&cudaStatus, "cudaMemcpy failed! :: classify_points_by_norm_memCopy", __LINE__);
}

void classify_points_by_norm_free(Point *dev_points, Centroid *dev_centroids)
{
	cudaFree(dev_points);
	cudaFree(dev_centroids);
}

void classify_points_by_norm(
	Point* points, int num_of_points,
	Centroid* const centroids, const int num_of_centroids,
	const int vector_size) {

	static cudaError_t cudaStatus;
	static int max_num_of_thr_per_block = get_max_num_of_threads_per_block();
	static int num_of_blocks = num_of_points / max_num_of_thr_per_block;

	Point *dev_points = NULL;
	Centroid *dev_centroids = NULL;

	classify_points_by_norm_alloc(
		&dev_points, num_of_points,
		&dev_centroids, num_of_centroids);

	classify_points_by_norm_memCopy(
		points, num_of_points,
		centroids, num_of_centroids,
		dev_points, dev_centroids);

	//kernel launch
	calc_norms << <num_of_blocks, max_num_of_thr_per_block >> >(dev_points, dev_centroids, num_of_centroids, vector_size);

	// Check for any errors launching the kernel
	cudaStatus = cudaGetLastError();
	check_cuda_status(&cudaStatus, "cudaGetLastError failed! :: classify_points_by_norm", __LINE__);

	// cudaDeviceSynchronize waits for the kernel to finish, and returns any errors encountered during the launch.
	cudaStatus = cudaDeviceSynchronize();
	check_cuda_status(&cudaStatus, "cudaDeviceSynchronize failed! :: classify_points_by_norm", __LINE__);

	cudaStatus = cudaMemcpy(points, dev_points, num_of_points * sizeof(Point), cudaMemcpyDeviceToHost);
	check_cuda_status(&cudaStatus, "cudaMemcpy failed! :: classify_points_by_norm", __LINE__);

	classify_points_by_norm_free(dev_points, dev_centroids);
}
////////////////////////////////















