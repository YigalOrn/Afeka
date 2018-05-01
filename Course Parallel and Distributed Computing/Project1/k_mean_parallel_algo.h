#pragma once

#include <omp.h>
#include <stdlib.h>

#include "my_data_types.h"
#include "kernel.h"
#include "math_util.h"


void k_mean_plus_init(const int centroids_size);

void k_mean_plus_free_init();

void do_k_mean_plus(
	Point *const points, const int points_size, 
	Centroid *const centroids, const int centroids_size, 
	Point *dev_points, Centroid *dev_centroids, int *dev_centroids_size,
	const int max_iterations, double *current_calculated_min_dis);

void zero_k_mean_sum_arrays(const int centroids_size);

void count_and_sum_after_norm_calc(const Point *const points, const int points_size, const int centroids_size);

void check_centroids(Centroid *centroids, const int centroids_size);

double get_min_dis_between_centroids(const Centroid *const centroids, const int centroids_size);

void calc_distances_between_centroids(double *min_distances_arr, const int min_distances_arr_size, const Centroid *const centroids, const int centroids_size);