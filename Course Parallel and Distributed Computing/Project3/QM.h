#pragma once

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>// for memcpy(..)

#include "MyStructs.h"




/*
*
*/
void alloc_QM_meta_data_structures(const int points_size, const int centroids_size, 
	float** centroids_dists_mat_ptr, float** centroids_diameters_arr_ptr, Point** cluster_points_ptr);
/*
*
*/
void free_QM_meta_data_structures(float* centroids_dists_mat, float* centroids_diameters_arr, Point* cluster_points);

/*
*
*/
float evaluateQuality(
	Point* const points, const int points_size,
	Centroid* const centroids, const int centroids_size,
	const int* const centroids_num_of_members,
	float* const centroids_dists_mat,
	float * const centroids_diameters_arr,
	Point* cluster_points);

/*
*
*/
void calc_distances_between_centroids(Centroid* const centroids, const int centroids_size, float* const meta_centroids_dists);

/*
*
*/
void calc_diameter_for_each_cluster(
	Point* points, const int points_size,
	const int centroids_size,
	const int*  const centroids_num_of_members,
	float* const centroids_diameters_arr,
	Point* cluster_points);

/*
*
*/
int sortPointsByCentroidIndex(const void* p1, const void* p2);