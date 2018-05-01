#pragma once

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "MyStructs.h"

/*
*
*/
int get_max_num_of_threads_per_block();

/*
*
*/
void set_points_to_work_with_cuda(Point **points_ptr, int *points_size_ptr);

/*
*
*/
void classify_points_by_norm(Point* points, const int points_size, Centroid* centroids, const int centroids_size);

/*
*
*/
void classify_points_by_norm_alloc(Point** dev_points_ptr, const int points_size, Centroid** dev_centroids_ptr, const int centroids_size);

/*
*
*/
void classify_points_by_norm_memCopy(Point* points, const int points_size, Centroid* centroids, const int centroids_size, Point* dev_points, Centroid* dev_centroids);

/*
*
*/
void classify_points_by_norm_free(Point* dev_points, Centroid* dev_centroids);
