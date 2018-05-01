#include "k_mean_parallel_algo.h"


////////////////////////////////
unsigned int *needMoreIterToConvergeArr = NULL;
double *centroids_sum_x = NULL, *centroids_sum_y = NULL;
int *centroids_num_of_members = NULL;
int i = -1, iterCtr = 0;
unsigned int needMoreIterToConverge;
double newCentroideX, newCentroideY;
////////////////////////////////

void k_mean_plus_init(const int centroids_size)
{
	needMoreIterToConvergeArr = (unsigned int*)malloc(centroids_size*sizeof(unsigned int)); 
	centroids_sum_x = (double*)malloc(centroids_size*sizeof(double));
	centroids_sum_y = (double*)malloc(centroids_size*sizeof(double));;
	centroids_num_of_members = (int*)malloc(centroids_size*sizeof(int));
}

void k_mean_plus_free_init()
{
	free(needMoreIterToConvergeArr);
	free(centroids_sum_x);
	free(centroids_sum_y);
	free(centroids_num_of_members);
}

void do_k_mean_plus(
	Point *const points, const int points_size, 
	Centroid *const centroids, const int centroids_size, 
	Point *dev_points, Centroid *dev_centroids, int *dev_centroids_size,
	const int max_iterations, double *current_calculated_min_dis)
{
	iterCtr = 0;

	do
	{
		++iterCtr;
		needMoreIterToConverge = 0;

		calc_points_norms(
			points, centroids, 
			dev_points, dev_centroids, 
			points_size, centroids_size, dev_centroids_size);
		zero_k_mean_sum_arrays(centroids_size);
		count_and_sum_after_norm_calc(points, points_size, centroids_size);
		check_centroids(centroids, centroids_size);

	} while( (iterCtr < max_iterations) && (needMoreIterToConverge));

	*current_calculated_min_dis = get_min_dis_between_centroids(centroids, centroids_size);
}

void zero_k_mean_sum_arrays(const int centroids_size)
{
	int i ;
#pragma omp parallel for default(shared) private(i)
	for(i=0; i<centroids_size; i++)
	{
		centroids_sum_x[i] = 0;
		centroids_sum_y[i] = 0;
		centroids_num_of_members[i] = 0;
		needMoreIterToConvergeArr[i] = 0;
	}
}

void count_and_sum_after_norm_calc(const Point *const points, const int points_size, const int centroids_size)
{
	//found that doing extra work is still fatser then doing some kind of synchronization!
	//using omp collapse(2), should increase performance, not available here!
	int i, j;

#pragma omp parallel for default(shared) private(i, j) 
	for(i=0; i<centroids_size; i++)
	{
		for(j=0; j<points_size; j++)
		{
			if( (!points[j].isDummyPoint) && (points[j].centroid_index == i) )
			{
				centroids_sum_x[i] += points[j].x;
				centroids_sum_y[i] += points[j].y;
				++(centroids_num_of_members[i]);
			}
		}
	}
}

void check_centroids(Centroid *centroids, const int centroids_size)
{
	int i;

#pragma omp parallel default(shared) private(i, newCentroideX, newCentroideY)
	{
#pragma omp for
		for(i=0; i<centroids_size; i++)
		{
			if(centroids_num_of_members[i] != 0)
			{
				newCentroideX = centroids_sum_x[i]/centroids_num_of_members[i];
				newCentroideY = centroids_sum_y[i]/centroids_num_of_members[i];
				if (centroids[i].x != newCentroideX || centroids[i].y != newCentroideY)
				{
					centroids[i].x = newCentroideX;
					centroids[i].y = newCentroideY;
					needMoreIterToConvergeArr[i] = 1;
				}
			}
		}

#pragma omp for reduction(|| : needMoreIterToConverge)
		for(i=0; i<centroids_size; i++)
		{
			needMoreIterToConverge = needMoreIterToConverge || needMoreIterToConvergeArr[i];
		}
	}
}

double get_min_dis_between_centroids(const Centroid *const centroids, const int centroids_size)
{
	double min_dis_result = -1;
	const int min_distances_arr_size = centroids_size - 1;
	double *min_distances_arr = (double*)malloc(sizeof(double)*min_distances_arr_size);

	calc_distances_between_centroids(min_distances_arr, min_distances_arr_size, centroids, centroids_size);
	min_dis_result = calc_min_dis_by_reduction(min_distances_arr, min_distances_arr_size);

	free(min_distances_arr);

	return min_dis_result;
}

void calc_distances_between_centroids(double *min_distances_arr, const int min_distances_arr_size, const Centroid *const centroids, const int centroids_size)
{
	double min_distance = INT_MAX*1.0;
	double temp_res;
	int i, j;

#pragma omp parallel for default(shared) private(i, j, temp_res) firstprivate(min_distance)
	for (i = 0; i < min_distances_arr_size; i++)
	{
		for (j = i + 1; j < centroids_size; j++)
		{
			temp_res = calc_norm(centroids[i].x, centroids[i].y, centroids[j].x, centroids[j].y);
			if (temp_res < min_distance)
			{
				min_distance = temp_res;
			}
		}
		min_distances_arr[i] = min_distance;
	}
}



