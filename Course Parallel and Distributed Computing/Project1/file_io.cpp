#include "file_io.h"


void create_project_format_file() 
{
	srand((unsigned int)time(NULL));
	
	FILE *output = fopen(file_path, "w");

	if (output == NULL) 
	{
		printf("%d-create_project_format_file :: file_io\n", __LINE__);
		system("PAUSE");
		exit(1);
	}

	int num_of_points, num_of_clusters, max_iterations, stat, T, time_delta;
	double a, b, R;

	num_of_points = rand() % 300001;
	num_of_clusters = 1 + (rand() % 100);
	max_iterations = rand() % 3001;

	init_time_interval_params(&T, &time_delta);

	stat = fprintf(output, "%d %d %lf %lf %d\n", num_of_points, num_of_clusters, time_delta*1.0, T*1.0, max_iterations);
	if (stat < 0) 
	{
		printf("%d-create_project_format_file :: file_io\n", __LINE__);
		system("PAUSE");
		exit(1);
	}

	for (int i = 0; i < num_of_points; i++)
	{
		a = rand() % 200 * 1.2;
		b = rand() % 100 * 0.3;
		R = rand() % 21 * 3.14;
		
		stat = fprintf(output, "%d %.3lf %.3lf %.3lf\n", i, a, b, R);
		if (stat < 0)
		{
			printf("%d-create_project_format_file :: file_io.cpp\n", __LINE__);
			system("PAUSE");
			exit(1);
		}
	}
	stat = fclose(output);
	if (stat < 0)
	{
		printf("%d-create_project_format_file :: file_io\n", __LINE__);
		system("PAUSE");
		exit(1);
	}
}

void init_time_interval_params(int *T_ptr, int *time_delta_ptr)
{
	int start = 5, end = 50;
	int divisor = get_numerator_and_divisor_denominator_in_bounds(T_ptr, start, end);
	*time_delta_ptr = *T_ptr/divisor;	
}

void read_project_format_file(Meta_Data *meta_data_ptr) 
{
	int num_of_points, num_of_clusters, max_iterations, index;
	double a, b, R, T, time_delta;

	FILE *input = fopen(file_path, "r");

	if (input == NULL)
	{
		printf("%d-read_project_format_file :: file_io.cpp\n", __LINE__);
		system("PAUSE");
		exit(1);
	}

	fscanf(input, "%d %d %lf %lf %d", &num_of_points, &num_of_clusters, &time_delta, &T, &max_iterations);

	meta_data_ptr->num_of_points = num_of_points;
	meta_data_ptr->num_of_clusters = num_of_clusters ;
	meta_data_ptr->time_delta = time_delta ;
	meta_data_ptr->T = T;
	meta_data_ptr->max_iterations = max_iterations;

	meta_data_ptr->vec_a = (double*)malloc(num_of_points * sizeof(double));
	meta_data_ptr->vec_b = (double*)malloc(num_of_points * sizeof(double));
	meta_data_ptr->vec_R = (double*)malloc(num_of_points * sizeof(double));

	while (!feof(input)) 
	{
		fscanf(input, "%d %lf %lf %lf", &index, &a, &b, &R);
		(meta_data_ptr->vec_a)[index] = a;
		(meta_data_ptr->vec_b)[index] = b;
		(meta_data_ptr->vec_R)[index] = R;
	}
	fclose(input);
}

void write_final_result_to_file(const double time, const double dis, const double *const centroids_x_y, const int centroid_size)
{
	int stat;
	FILE *output = fopen(final_result_file_path, "w");

	if (output == NULL) 
	{
		printf("%d-write_final_result_to_file :: file_io\n", __LINE__);
		system("PAUSE");
		exit(1);
	}

	stat = fprintf(output, "time: %.3lf\nmin distance: %.3lf\n", time, dis);
	if (stat < 0) 
	{
		printf("%d-write_final_result_to_file :: file_io\n", __LINE__);
		system("PAUSE");
		exit(1);
	}

	int k=0;
	for (int i = 0; i < centroid_size*2; i+=2)
	{
		stat = fprintf(output, "%d - x: %.3lf\ty: %.3lf\n", k++,centroids_x_y[i], centroids_x_y[i+1]);
		if (stat < 0)
		{
			printf("%d-write_final_result_to_file :: file_io\n", __LINE__);
			system("PAUSE");
			exit(1);
		}
	}

	stat = fclose(output);
	if (stat < 0)
	{
		printf("%d-write_final_result_to_file :: file_io\n", __LINE__);
		system("PAUSE");
		exit(1);
	}
}
