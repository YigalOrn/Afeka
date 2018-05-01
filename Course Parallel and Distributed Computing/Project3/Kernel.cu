#include "Kernel.h"


////////////////////////////////
__global__ void calc_norms(Point * dev_points, const int points_size, Centroid* dev_centroids, const int centroids_size) {
	int block_size = blockDim.x;

	float temp_norm, pointX, pointY, centroidX, centroidY;

	if (!dev_points[blockIdx.x*block_size + threadIdx.x].isDummyPoint)
	{
		pointX = dev_points[blockIdx.x*block_size + threadIdx.x].x;
		pointY = dev_points[blockIdx.x*block_size + threadIdx.x].y;

		//init first norm
		centroidX = dev_centroids[0].x;
		centroidY = dev_centroids[0].y;
		dev_points[blockIdx.x*block_size + threadIdx.x].minDisFromCentroid = sqrt(pow((pointX - centroidX), 2) + pow((pointY - centroidY), 2));
		dev_points[blockIdx.x*block_size + threadIdx.x].myCentroidIndex = 0;

		//do the rest
		for (int i = 1; i<centroids_size; i++)
		{
			centroidX = dev_centroids[i].x;
			centroidY = dev_centroids[i].y;

			temp_norm = sqrt(pow(pointX - centroidX, 2) + pow(pointY - centroidY, 2));

			if (temp_norm < dev_points[blockIdx.x*block_size + threadIdx.x].minDisFromCentroid)
			{
				dev_points[blockIdx.x*block_size + threadIdx.x].minDisFromCentroid = temp_norm;
				dev_points[blockIdx.x*block_size + threadIdx.x].myCentroidIndex = i;
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

void set_points_to_work_with_cuda(Point **points_ptr, int *points_size_ptr)
{
	int current_points_size = *points_size_ptr;
	int max_thr_per_block = get_max_num_of_threads_per_block();
	int left_points = -1;

	//in case: we dont have an integer number of blocks
	if ((left_points = (*points_size_ptr) % max_thr_per_block) != 0)
	{
		*points_size_ptr = current_points_size + (max_thr_per_block - left_points);
		(*points_ptr) = (Point*)realloc((*points_ptr), sizeof(Point)*(*points_size_ptr));// shallow copy is ok here
	}
}

void classify_points_by_norm_alloc(Point** dev_points_ptr, const int points_size, Centroid** dev_centroids_ptr, const int centroids_size) {
	static cudaError_t cudaStatus;

	cudaStatus = cudaMalloc((void**)dev_points_ptr, sizeof(Point)*points_size);
	check_cuda_status(&cudaStatus, "cudaMalloc failed! :: classify_points_by_norm_alloc", __LINE__);

	cudaStatus = cudaMalloc((void**)dev_centroids_ptr, sizeof(Centroid)*centroids_size);
	check_cuda_status(&cudaStatus, "cudaMalloc failed! :: classify_points_by_norm_alloc", __LINE__);
}

void classify_points_by_norm_memCopy(Point* points, const int points_size, Centroid* centroids, const int centroids_size, Point* dev_points, Centroid* dev_centroids) {
	static cudaError_t cudaStatus;

	cudaStatus = cudaMemcpy(dev_points, points, points_size * sizeof(Point), cudaMemcpyHostToDevice);
	check_cuda_status(&cudaStatus, "cudaMemcpy failed! :: classify_points_by_norm_memCopy", __LINE__);

	cudaStatus = cudaMemcpy(dev_centroids, centroids, centroids_size * sizeof(Centroid), cudaMemcpyHostToDevice);
	check_cuda_status(&cudaStatus, "cudaMemcpy failed! :: classify_points_by_norm_memCopy", __LINE__);
}

void classify_points_by_norm_free(Point* dev_points, Centroid* dev_centroids) {
	cudaFree(dev_points);
	cudaFree(dev_centroids);
}

////////////////////////////////

////////////////////////////////
void classify_points_by_norm(Point* points, const int points_size, Centroid* centroids, const int centroids_size) {

	static cudaError_t cudaStatus;
	static int max_num_of_thr_per_block = get_max_num_of_threads_per_block();
	static int num_of_blocks = points_size / max_num_of_thr_per_block;// we changed points size to be eqaully divided into max number of blocks for this GPU

	Point *dev_points = NULL;
	Centroid *dev_centroids = NULL;

	classify_points_by_norm_alloc(&dev_points, points_size, &dev_centroids, centroids_size);

	classify_points_by_norm_memCopy(points, points_size, centroids, centroids_size, dev_points, dev_centroids);

	//kernel launch
	calc_norms <<<num_of_blocks, max_num_of_thr_per_block >>> (dev_points, points_size, dev_centroids, centroids_size);

	// Check for any errors launching the kernel
	cudaStatus = cudaGetLastError();
	check_cuda_status(&cudaStatus, "cudaGetLastError failed! :: classify_points_by_norm", __LINE__);

	// cudaDeviceSynchronize waits for the kernel to finish, and returns any errors encountered during the launch
	cudaStatus = cudaDeviceSynchronize();
	check_cuda_status(&cudaStatus, "cudaDeviceSynchronize failed! :: classify_points_by_norm", __LINE__);

	cudaStatus = cudaMemcpy(points, dev_points, points_size * sizeof(Point), cudaMemcpyDeviceToHost);
	check_cuda_status(&cudaStatus, "cudaMemcpy failed! :: classify_points_by_norm", __LINE__);

	classify_points_by_norm_free(dev_points, dev_centroids);
}
////////////////////////////////











