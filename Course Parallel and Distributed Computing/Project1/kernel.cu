#include "kernel.h"


////////////////////////////////
__global__ void calc_norms(Point *dev_points, const Centroid *const dev_centroids, const int *const dev_centroids_size)
{
	int block_size = blockDim.x;

	double temp_norm, pointX, pointY, centroidX, centroidY;

	if(!dev_points[blockIdx.x*block_size + threadIdx.x].isDummyPoint)
	{
		pointX = dev_points[blockIdx.x*block_size + threadIdx.x].x;
		pointY = dev_points[blockIdx.x*block_size + threadIdx.x].y;

		//init first norm
		centroidX = dev_centroids[0].x;
		centroidY = dev_centroids[0].y;
		dev_points[blockIdx.x*block_size + threadIdx.x].min_dis = sqrt( pow((pointX-centroidX),2) + pow((pointY-centroidY),2) );
		dev_points[blockIdx.x*block_size + threadIdx.x].centroid_index = 0;

		//do the rest
		for(int i=1; i<(*dev_centroids_size); i++)
		{
			centroidX = dev_centroids[i].x;
			centroidY = dev_centroids[i].y;

			temp_norm =  sqrt( pow(pointX-centroidX,2) + pow(pointY-centroidY,2) );

			if(temp_norm < dev_points[blockIdx.x*block_size + threadIdx.x].min_dis)
			{
				dev_points[blockIdx.x*block_size + threadIdx.x].min_dis = temp_norm;
				dev_points[blockIdx.x*block_size + threadIdx.x].centroid_index = i;
			}	
		}
	}
}

__global__ void do_reduction(double *dev_reduction_arr)
{
	int nTotalThreads = blockDim.x;
	int halfPoint;
	int j;
	double temp_res;

	while (nTotalThreads > 1) 
	{
		halfPoint = nTotalThreads >> 1;
		if (threadIdx.x < halfPoint) 
		{
			j = threadIdx.x + halfPoint;
			temp_res = dev_reduction_arr[j];
			if (temp_res < dev_reduction_arr[threadIdx.x]) 
			{
				dev_reduction_arr[threadIdx.x] = temp_res;
			}
		}

		__syncthreads();

		nTotalThreads = nTotalThreads >> 1;

	}//while
}
////////////////////////////////


////////////////////////////////
void check_cuda_status(const cudaError_t *const cudaStatus, const char *const error_msg, const int line_number)
{
	if (*cudaStatus != cudaSuccess) 
	{
		printf("%d-%s\n", (line_number-1), error_msg);
		printf("%s\n", cudaGetErrorString(*cudaStatus));
		system("PAUSE");
		exit(1);
	}
}

void alloc_params_for_cuda(
	Point **dev_points_ptr, const int points_size, 
	Centroid **dev_centroids_ptr, const int centroids_size,
	int ** dev_centroids_size_ptr)
{
	cudaError_t cudaStatus;

	cudaStatus = cudaMalloc((void**)dev_points_ptr, sizeof(Point)*points_size);
	check_cuda_status(&cudaStatus, "cudaMalloc failed! :: alloc_params_for_cuda", __LINE__);

	cudaStatus = cudaMalloc((void**)dev_centroids_ptr, sizeof(Centroid)*centroids_size);
	check_cuda_status(&cudaStatus, "cudaMalloc failed! :: alloc_params_for_cuda", __LINE__);

	cudaStatus = cudaMalloc((void**)dev_centroids_size_ptr, sizeof(int));
	check_cuda_status(&cudaStatus, "cudaMalloc failed! :: alloc_params_for_cuda", __LINE__);

	//one immediate initialization
	cudaStatus = cudaMemcpy((*dev_centroids_size_ptr), &centroids_size, sizeof(int), cudaMemcpyHostToDevice);
	check_cuda_status(&cudaStatus, "cudaMemcpy failed! :: alloc_params_for_cuda", __LINE__);
}

void free_params_for_cuda(Point *dev_points, Centroid *dev_centroids, int* dev_centroids_size)
{
	cudaFree(dev_points);
	cudaFree(dev_centroids);
	cudaFree(dev_centroids_size);
}

int get_max_num_of_threads_per_block()
{
	struct cudaDeviceProp properties;
	cudaGetDeviceProperties(&properties, 0);
	return properties.maxThreadsPerBlock;
}
////////////////////////////////


////////////////////////////////
void calc_points_norms(
	Point *points, Centroid *centroids, 
	Point * dev_points, Centroid *dev_centroids, 
	const int points_size, const int centroids_size, 
	int *dev_centroids_size)
{
	cudaError_t cudaStatus;

	int max_num_of_thr_per_block = get_max_num_of_threads_per_block();
	int num_of_blocks = points_size/max_num_of_thr_per_block;

	dim3 BlockDim(max_num_of_thr_per_block, 1, 1);
	dim3 GridDim(num_of_blocks, 1, 1);


	cudaStatus = cudaMemcpy(dev_points, points, points_size * sizeof(Point), cudaMemcpyHostToDevice);
	check_cuda_status(&cudaStatus, "cudaMemcpy failed! :: init_params_for_cuda", __LINE__);

	cudaStatus = cudaMemcpy(dev_centroids, centroids, centroids_size * sizeof(Centroid), cudaMemcpyHostToDevice);
	check_cuda_status(&cudaStatus, "cudaMemcpy failed! :: init_params_for_cuda", __LINE__);

	//kernel launch
	calc_norms<<<GridDim, BlockDim>>>(dev_points, dev_centroids, dev_centroids_size);

	// Check for any errors launching the kernel
	cudaStatus = cudaGetLastError();
	check_cuda_status(&cudaStatus, "cudaGetLastError failed! :: calc_points_norms", __LINE__);

	// cudaDeviceSynchronize waits for the kernel to finish, and returns any errors encountered during the launch.
	cudaStatus = cudaDeviceSynchronize();
	check_cuda_status(&cudaStatus, "cudaDeviceSynchronize failed! :: calc_points_norms", __LINE__);

	cudaStatus = cudaMemcpy(points, dev_points, points_size * sizeof(Point), cudaMemcpyDeviceToHost);
	check_cuda_status(&cudaStatus, "cudaMemcpy failed! :: init_params_for_cuda", __LINE__);	
}

double calc_min_dis_by_reduction(double *const min_distances_arr, const int min_distances_arr_size)
{
	cudaError_t cudaStatus;
	double *dev_reduction_arr = NULL;
	double result = -1;
	int reduction_arr_size = min_distances_arr_size;

	find_nearest_power_of_2(&reduction_arr_size);

	double *reduction_arr = (double*)malloc(sizeof(double)*reduction_arr_size);
	memcpy(reduction_arr, min_distances_arr, min_distances_arr_size * sizeof(double));

	for (int i = min_distances_arr_size; i < reduction_arr_size; i++)
	{
		reduction_arr[i] = min_distances_arr[i - min_distances_arr_size];
	}

	cudaStatus = cudaMalloc((void**)&dev_reduction_arr, reduction_arr_size * sizeof(double));
	check_cuda_status(&cudaStatus, "cudaMalloc failed! :: calc_min_dis_by_reduction", __LINE__);

	cudaStatus = cudaMemcpy(dev_reduction_arr, reduction_arr, reduction_arr_size * sizeof(double), cudaMemcpyHostToDevice);
	check_cuda_status(&cudaStatus, "cudaMemcpy failed! :: calc_min_dis_by_reduction", __LINE__);

	//kernel call
	do_reduction<<<1, reduction_arr_size>>>(dev_reduction_arr);

	// Check for any errors launching the kernel
	cudaStatus = cudaGetLastError();
	check_cuda_status(&cudaStatus, "cudaGetLastError failed! :: calc_min_dis_by_reduction", __LINE__);

	// cudaDeviceSynchronize waits for the kernel to finish, and returns any errors encountered during the launch.
	cudaStatus = cudaDeviceSynchronize();
	check_cuda_status(&cudaStatus, "cudaDeviceSynchronize failed! :: calc_min_dis_by_reduction", __LINE__);

	cudaStatus = cudaMemcpy(reduction_arr, dev_reduction_arr, reduction_arr_size * sizeof(double), cudaMemcpyDeviceToHost);
	check_cuda_status(&cudaStatus, "cudaMemcpy failed! :: calc_min_dis_by_reduction", __LINE__);

	result = reduction_arr[0] ;

	cudaFree(dev_reduction_arr);
	free(reduction_arr);

	return result;
}
////////////////////////////////




