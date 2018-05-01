#include "QM.h"

void alloc_QM_meta_data_structures(const int points_size, const int centroids_size, float** centroids_dists_mat_ptr, float** centroids_diameters_arr_ptr, Point** cluster_points_ptr) {
	
	(*centroids_dists_mat_ptr) = (float*)malloc(sizeof(float)*(centroids_size*centroids_size));
	(*centroids_diameters_arr_ptr) = (float*)malloc(sizeof(float)*centroids_size);
	(*cluster_points_ptr) = (Point*)malloc(sizeof(Point)*points_size);

	if ((*centroids_dists_mat_ptr) == NULL || (*centroids_diameters_arr_ptr) == NULL || (*cluster_points_ptr) == NULL) {
		printf("%d - alloc_QM_meta_data_structures :: QMcpp\n", __LINE__);
		system("PAUSE");
		exit(0);
	}
}

void free_QM_meta_data_structures(float* centroids_dists_mat, float* centroids_diameters_arr, Point* cluster_points) {
	free(centroids_dists_mat);
	free(centroids_diameters_arr);
	free(cluster_points);
}

/*
* # declare and define in a dedicated QM.h and QM.cpp where needed
*
* func args:
*
* # both already defined and just need to be passed
* - points, points_size
*
* # both already defined and just need to be passed
* - centroids, centroids_size
*
* # already defined and just need to be passed
* - centroids_num_of_members
*
* # this is a matrix as array of size: centroids_size*centroids_size
* # this matrix is predefined i.e allocated to be used in each time iter for the q calc` without allocate/free each for each time slot
* # the choice of a matrix is space-time trade off to be used with openmp
* - meta_centroids_dists
*
* # an array of size: centroids_size, that holds the diameters for the current time iter
* - centroids_diameters
*
* # just a place holder for each final cluster points to be used when calc the diameter of each cluster
* - cluster_points
*
* */
float evaluateQuality(
	Point* const points, const int points_size,
	Centroid* const centroids, const int centroids_size,
	const int* const centroids_num_of_members,
	float* const centroids_dists_mat,
	float * const centroids_diameters_arr,
	Point* cluster_points) {

	// 1)
	calc_distances_between_centroids(centroids, centroids_size, centroids_dists_mat);

	// 2)
	calc_diameter_for_each_cluster(points, points_size, centroids_size, centroids_num_of_members, centroids_diameters_arr, cluster_points);

	// 3)
	// now we have all data, lets calc the qm for this time iter, return result
	float q = 0, d;
	int number_of_elements_to_sum_in_q = -1, j;

	for (int i = 0; i < centroids_size; ++i)
	{
		d = centroids_diameters_arr[i];

		j = 0;
		while (j < centroids_size) {
			if (j != i)
			{
				if (centroids_dists_mat[i*centroids_size + j] != -1)
				{
					q += (d / centroids_dists_mat[i*centroids_size + j]);
				}
				else if (centroids_dists_mat[i*centroids_size + j] == -1)
				{
					q += (d / centroids_dists_mat[j*centroids_size + i]);
				}
			}
			++j;
		}
	}

	number_of_elements_to_sum_in_q = (centroids_size*(centroids_size - 1));

	q /= number_of_elements_to_sum_in_q;

	return q;
}

void calc_distances_between_centroids(Centroid* const centroids, const int centroids_size, float* const meta_centroids_dists) {

	int i, j;
	float temp = 0;

#pragma omp parallel default(shared) private(i, j) firstprivate(temp)
	{
		// init distances in matrix with immpossible values
		// dis>=0
#pragma omp for schedule(static)
		for (i = 0; i < centroids_size; i++) {
			for (j = 0; j < centroids_size; j++) {
				meta_centroids_dists[i * centroids_size + j] = -1;
			}
		}

#pragma omp for schedule(static)
		for (i = 0; i < centroids_size; i++) {
			for (j = i + 1; j < centroids_size; j++) {
				temp += pow(centroids[i].x - centroids[j].x, 2) + pow(centroids[i].y - centroids[j].y, 2);
				if (temp != 0)
				{
					meta_centroids_dists[i * centroids_size + j] = sqrt(temp);
					temp = 0;
				}
			}
		}
	}
}

void calc_diameter_for_each_cluster(
	Point* points, const int points_size, 
	const int centroids_size, 
	const int*  const centroids_num_of_members,
	float* const centroids_diameters_arr,
	Point* cluster_points) {


	// sort points by cluster id
	// we dont care sorting the points array! because next time iter we init them again!
	qsort(points, points_size, sizeof(Point), sortPointsByCentroidIndex);

	// set each cluster pivot
	Point* curr_start = points;

	// set end of points indicator
	Point* points_end_ptr = points + points_size;

	int v = -1, i = -1, j = -1; // indices
	int jump = 0, size = -1;
	float max = 0, temp = 0;

	// for cluster calc its diameter
	for (v = 0; v < centroids_size; ++v)
	{
		// size of chunk for omp to work with
		size = centroids_num_of_members[v];

		if (size >= 2) {

			memcpy(cluster_points, curr_start, sizeof(Point)*size);

			// calc cluster v diameter using omp
#pragma omp parallel for default(shared) private(i, j) firstprivate(temp) schedule(static)
			for (i = 0; i < size; ++i)
			{
				for (j = i + 1; j < size; ++j)
				{
					temp = sqrt(pow(cluster_points[i].x - cluster_points[j].x, 2) + pow(cluster_points[i].y - cluster_points[j].y, 2));
#pragma omp critical
					{
						if (max < temp) {
							max = temp;
						}
					}
					temp = 0;
				}
			}
			centroids_diameters_arr[v] = max;
		}
		else {
			centroids_diameters_arr[v] = 0;
		}

		// zero max for next centroid iter
		max = 0;

		// set jump as centroids_num_of_members[v];
		jump = size;
		// set the pointer to the start of the wanted points chunk
		curr_start += jump;
	}
}

int sortPointsByCentroidIndex(const void* p1, const void* p2) {

	int l = ((Point*)p1)->myCentroidIndex;
	int r = ((Point*)p2)->myCentroidIndex;
	return (l - r);
}





