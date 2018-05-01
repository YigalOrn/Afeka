#pragma once

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include "MyStructs.h"


int get_max_num_of_threads_per_block();

void set_points_to_work_with_cuda(Point **points_ptr, int *points_size_ptr);

void classify_points_by_norm(
	Point*  points, int num_of_points,
	Centroid* centroids, const int num_of_centroids,
	const int vector_size);



