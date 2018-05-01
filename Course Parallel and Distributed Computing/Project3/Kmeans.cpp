#include "Kmeans.h"


void alloc_k_means_meta_data_structures(const int centroids_size, unsigned int** need_more_iter_to_converge_arr_Ptr,
	float** centroids_x_sum_Ptr, float**centroids_y_sum_Ptr,
	int** centroids_num_of_members_Ptr) {

	(*need_more_iter_to_converge_arr_Ptr) = (unsigned int*)malloc(centroids_size * sizeof(unsigned int));
	(*centroids_x_sum_Ptr) = (float*)malloc(centroids_size * sizeof(float));
	(*centroids_y_sum_Ptr) = (float*)malloc(centroids_size * sizeof(float));
	(*centroids_num_of_members_Ptr) = (int*)malloc(centroids_size * sizeof(int));

	if ((*need_more_iter_to_converge_arr_Ptr) == NULL || (*centroids_x_sum_Ptr)==NULL || (*centroids_y_sum_Ptr)==NULL || (*centroids_num_of_members_Ptr)==NULL) {
		printf("%d - alloc_k_means_meta_data_structures :: Kmeans.cpp\n", __LINE__);
		system("PAUSE");
		exit(0);
	}
}

void free_k_means_meta_data_structures(unsigned int* need_more_iter_to_converge_arr,
	float* centroids_x_sum, float*centroids_y_sum,
	int* centroids_num_of_members) {
	free(need_more_iter_to_converge_arr);
	free(centroids_x_sum);
	free(centroids_y_sum);
	free(centroids_num_of_members);
}

void k_means(
	const int rank,
	const int K, const int LIMIT,
	Point* points, const int points_size, Centroid* centroids, const int centroids_size,
	unsigned int* need_more_iter_to_converge_arr,
	float*centroids_x_sum, float*centroids_y_sum, int*centroids_num_of_members) {

	int iterCtr = 0;
	static unsigned int needMoreIterToConverge;

	do {
		// set def to false each local round
		needMoreIterToConverge = 0;
		++iterCtr;

		// 1) classify points to centroids (CUDA)
		classify_points_by_norm(points, points_size, centroids, centroids_size);

		// 2) for each cluster: sum its points and members (openMP)
		zero_meta_data_structures(centroids_size, need_more_iter_to_converge_arr, centroids_x_sum, centroids_y_sum, centroids_num_of_members);
		count_and_sum_after_classification_by_norm(points, points_size, centroids_size, centroids_x_sum, centroids_y_sum, centroids_num_of_members);

		// 3) check if centroids changed (openMP)
		needMoreIterToConverge = check_centroids_for_changes(centroids, centroids_size, need_more_iter_to_converge_arr, centroids_x_sum, centroids_y_sum, centroids_num_of_members);

	} while ((iterCtr < LIMIT) && (needMoreIterToConverge));
}

void zero_meta_data_structures(const int centroids_size, unsigned int* need_more_iter_to_converge_arr,
	float* centroids_x_sum, float* centroids_y_sum, int *centroids_num_of_members) {

	int i = -1;

#pragma omp parallel for default(shared) private(i) schedule(static)
	for (i = 0; i < centroids_size; i++)
	{
		need_more_iter_to_converge_arr[i] = 0;
		centroids_x_sum[i] = 0;
		centroids_y_sum[i] = 0;
		centroids_num_of_members[i] = 0;
	}
}

void count_and_sum_after_classification_by_norm(Point* points, const int points_size, const int centroids_size,
	float* centroids_x_sum, float* centroids_y_sum, int* centroids_num_of_members) {

	// found that doing extra work is still fatser then doing some kind of synchronization!
	// using omp collapse(2), should increase performance, not available here, VS has omp 2.0v !!!
	int i = -1, j = -1;

#pragma omp parallel for default(shared) private(i, j)  
	for (i = 0; i < centroids_size; i++)
	{
		for (j = 0; j < points_size; j++)
		{
			if ((!points[j].isDummyPoint) && (points[j].myCentroidIndex == i))
			{
				centroids_x_sum[i] += points[j].x;
				centroids_y_sum[i] += points[j].y;
				++(centroids_num_of_members[i]);
			}
		}
	}
}

int check_centroids_for_changes(Centroid* centroids, const int centroids_size, 
	unsigned int* need_more_iter_to_converge_arr,
	float* centroids_x_sum, float* centroids_y_sum, int* centroids_num_of_members) {
	
	int i=-1;
	unsigned int needMoreIterToConverge = 0;
	float newCentroideX, newCentroideY;

#pragma omp parallel default(shared) private(i, newCentroideX, newCentroideY)
	{
#pragma omp for
		for (i = 0; i < centroids_size; i++)
		{
			if (centroids_num_of_members[i] != 0)
			{
				newCentroideX = centroids_x_sum[i] / centroids_num_of_members[i];
				newCentroideY = centroids_y_sum[i] / centroids_num_of_members[i];
				if (centroids[i].x != newCentroideX || centroids[i].y != newCentroideY)
				{
					centroids[i].x = newCentroideX;
					centroids[i].y = newCentroideY;
					need_more_iter_to_converge_arr[i] = 1;
				}
			}
		}

#pragma omp for reduction(|| : needMoreIterToConverge)
		for (i = 0; i < centroids_size; i++)
		{
			needMoreIterToConverge = needMoreIterToConverge || need_more_iter_to_converge_arr[i];
		}
	}

	return needMoreIterToConverge;
}