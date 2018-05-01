#pragma once

#include "MyStructs.h"
#include "Kernel.h"

/*
* rank is for debug only
*/
void k_means(
	const int rank,
	const int K, const int LIMIT,
	Point* points, const int points_size, Centroid* centroids, const int centroids_size,
	unsigned int* need_more_iter_to_converge_arr,
	float*centroids_x_sum, float*centroids_y_sum, int*centroids_num_of_members);
/*
*
*/
void alloc_k_means_meta_data_structures(const int centroids_size, unsigned int** need_more_iter_to_converge_arr_Ptr,
	float** centroids_x_sum_Ptr, float**centroids_y_sum_Ptr, 
	int** centroids_num_of_members_Ptr);

/*
*
*/
void free_k_means_meta_data_structures(unsigned int* need_more_iter_to_converge_arr,
	float* centroids_x_sum, float*centroids_y_sum,
	int* centroids_num_of_members);

/*
*
*/
void zero_meta_data_structures(const int centroids_size, unsigned int* need_more_iter_to_converge_arr,
	float* centroids_x_sum, float* centroids_y_sum, int *centroids_num_of_members);

/*
*
*/
void count_and_sum_after_classification_by_norm(Point* points, const int points_size, const int centroids_size,
	float* centroids_x_sum, float* centroids_y_sum, int* centroids_num_of_members);

/*
*
*/
int check_centroids_for_changes(Centroid* centroids, const int centroids_size,
	unsigned int* need_more_iter_to_converge_arr,
	float* centroids_x_sum, float* centroids_y_sum, int* centroids_num_of_members);