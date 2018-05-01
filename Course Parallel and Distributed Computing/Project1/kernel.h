#pragma once

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "my_data_types.h"
#include "math_util.h"


/*
takes an array of points.
each cuda-thread that is created is responsible for calculating 
the min dis from this point to all centroids(passed as an arg also).
*/
__global__ void calc_norms(Point *dev_points, const Centroid *const dev_centroids, const int *const dev_centroids_size);

/*
this function gets an array of type double, this array is custom made! 
to be used in CUDA. the array contains all distances between centroids
for a given k-mean "step".
using CUDA-threads it will
do a kind of a binary-search reduce eventually putting in the device array
at the forst index the wanted result.
*/
__global__ void do_reduction(double *dev_reduction_arr);

/*
utility function that gives back the GPU information in this case 
the number of maximumj threads that could be lunched in a single block.
*/
int get_max_num_of_threads_per_block();

/*
utility function to check CUDA errors when CUDA related code is processed.
*/
void check_cuda_status(const cudaError_t *const cudaStatus, const char *const error_msg, const int line_number);

void alloc_params_for_cuda(
	Point **dev_points_ptr, const int points_size, 
	Centroid **dev_centroids_ptr, const int centroids_size,
	int ** dev_centroids_size_ptr);

void free_params_for_cuda(Point *dev_points, Centroid *dev_centroids, int* dev_centroids_size);

/*
initializes the previouslly allocated space on the device to be
used in the kernel functions. 
*/
void init_params_for_cuda(
	Point *points, Centroid *centroids, 
	Point *dev_points, Centroid *dev_centroids, 
	const int points_size, const int centroids_size);

/*
an entry point for the do_k_mean_plus(...) function,
this function will launch the kernel that will calculate the closest centroid
for each point.
*/
void calc_points_norms(
	Point *points, Centroid *centroids, 
	Point * dev_points, Centroid *dev_centroids, 
	const int points_size, const int centroids_size, 
	int *dev_centroids_size);

/*
do_k_mean_plus(...) after this function get the final centroids, we need to get the min dis between them, it will use as an entry point to CUDA kernel function
this function to get the min dis between them.
*/
double calc_min_dis_by_reduction(double *const min_distances_arr, const int min_distances_arr_size);
