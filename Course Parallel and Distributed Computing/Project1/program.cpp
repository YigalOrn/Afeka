#include "program.h"


//#define CREATE_PROJECT_FORMAT_FILE
//#define DEBUG_LOCAL_RESULTS
//#define DEBUG_TIME_DISTRIBUTION


int main(int argc, char *argv[])
{
	////////////////////////////////
	const int root = 0;
	int my_rank = -1, num_of_procs = -1;
	////////////////////////////////

	////////////////////////////////
	double start_time = -1, finish_time = -1;
	Result my_result;
	Meta_Data meta_data;
	int t_array_size = -1, my_t_array_chunk = -1;
	double *t_array = NULL, *my_t_array = NULL;
	////////////////////////////////

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_of_procs);

	////////////////////////////////
	//Program Run Time
	if(my_rank == root) 
	{ 
		start_time = MPI_Wtime();
		printf("Parallel K Mean Plus Algorithm Started...\n");
		fflush(stdout);
	}
	////////////////////////////////

	////////////////////////////////
	//Master reads meta data and distributes it among participating machines
	get_meta_data(&meta_data, my_rank, root);
	////////////////////////////////

	////////////////////////////////
	//Master Divides t-values among participating machines
	get_t_array_chunk(&meta_data, &t_array, &t_array_size, &my_t_array, &my_t_array_chunk, my_rank, root, num_of_procs);
	////////////////////////////////

	////////////////////////////////
	//Master checks for left-over after ditribution, it gives the root(it self) the rest
	if (my_rank == root)
	{ 
		check_t_array_left_overs(&t_array, t_array_size,&my_t_array, &my_t_array_chunk, num_of_procs); 
	}
	////////////////////////////////

#ifdef DEBUG_TIME_DISTRIBUTION
	char file_path[100] = "D:\\ZZZ_Final_Project_VS_2010\\Project\\Project\\my_time_chunk\\";
	char my_rank_str[20];
	sprintf(my_rank_str, "%d", my_rank);
	strcat(my_rank_str,".txt");
	strcat(file_path, my_rank_str);

	FILE *output = fopen(file_path, "w");
	for(int i=0; i<my_t_array_chunk; i++)
	{
		fprintf(output, "%.3f\n", my_t_array[i]);
	}
	fclose(output);
#endif

	////////////////////////////////
	//Each machine will calculate the min distance(including other relevant params) for her chunk of t's, each machine result is in my_result struct.
	calc_min_distance(&meta_data, my_t_array, my_t_array_chunk, &my_result, my_rank);
	////////////////////////////////

	////////////////////////////////
	//finding the absolute min_dis, Master outputs result to file
	finding_the_absolute_min_dis(root, my_rank, &my_result, num_of_procs, meta_data.num_of_clusters);
	////////////////////////////////

	////////////////////////////////
	//freeing any -mutual- allocated resources
	final_program_free(my_t_array, &meta_data, &my_result);
	////////////////////////////////

	////////////////////////////////
	//Program Run Time

	MPI_Barrier(MPI_COMM_WORLD);//only needed for runtime

	if (my_rank == root)
	{
		finish_time = MPI_Wtime();
		printf("$ runtime: %.5f sec, %.5f min $\n", finish_time-start_time, (finish_time-start_time)/60.0);
		fflush(stdout);
	}
	////////////////////////////////

	MPI_Finalize();

	return 0;
}

void final_program_free(double *my_t_array, Meta_Data *meta_data_ptr, Result *my_result_ptr)
{
	free(my_t_array);
	free(meta_data_ptr->vec_a);//allocated in :: calc_min_distance(...)
	free(meta_data_ptr->vec_b);//allocated in :: calc_min_distance(...)
	free(meta_data_ptr->vec_R);//allocated in :: calc_min_distance(...)
	free(my_result_ptr->centroids);//allocated in :: calc_min_distance(...)
}

void get_meta_data(Meta_Data *meta_data_ptr, const int my_rank, const int root)
{
	char *buffer = NULL;
	int pos = -1;

	if (my_rank == root)
	{

#ifdef CREATE_PROJECT_FORMAT_FILE
		create_project_format_file();
#endif

		read_project_format_file(meta_data_ptr);
		pack_buffer(&buffer, meta_data_ptr, &pos);
	}

	//also serves as an implicit barrier
	//notice pos had been initialized in pack_buffer(...) 
	MPI_Bcast(&pos, 1, MPI_INT, root, MPI_COMM_WORLD);

	if (my_rank != root)
	{
		buffer = (char*)malloc(sizeof(char)*pos);
	}

	MPI_Bcast(buffer, pos, MPI_PACKED, root, MPI_COMM_WORLD);
	unpack_buffer(buffer, meta_data_ptr, pos, &pos);

	free(buffer);
}

void get_t_array_chunk(
	const Meta_Data *const meta_data_ptr,
	double **t_array_ptr, int *t_array_size_ptr,
	double **my_t_array_ptr, int *my_t_array_chunk_ptr, 
	const int my_rank, const int root, const int num_of_procs)
{
	if (my_rank == root)
	{
		init_t_array(t_array_ptr, t_array_size_ptr, my_t_array_chunk_ptr, num_of_procs, meta_data_ptr->time_delta, meta_data_ptr->T);
	}

	MPI_Bcast(my_t_array_chunk_ptr, 1, MPI_INT, root, MPI_COMM_WORLD);

	(*my_t_array_ptr) = (double*)malloc( (*my_t_array_chunk_ptr) * sizeof(double));

	MPI_Scatter((*t_array_ptr), (*my_t_array_chunk_ptr), MPI_DOUBLE, (*my_t_array_ptr), (*my_t_array_chunk_ptr), MPI_DOUBLE, root, MPI_COMM_WORLD);
}

void check_t_array_left_overs(
	double** t_array_ptr, const int t_array_size,
	double** my_t_array_ptr, int *my_t_array_chunk_ptr, 
	const int num_of_procs)
{	
	if (( (*my_t_array_chunk_ptr) * num_of_procs) != t_array_size)
	{
		int left_size = t_array_size % num_of_procs;
		(*my_t_array_ptr) = (double*)realloc( (*my_t_array_ptr), ( (*my_t_array_chunk_ptr) + left_size) * sizeof(double));//roots chunk of time-t's

		//root gets the left over from the end of the t_array
#pragma omp parallel for default(shared)
		for (int i = 0; i < left_size; i++)
		{
			(*my_t_array_ptr)[ (*my_t_array_chunk_ptr) + i] = (*t_array_ptr)[(t_array_size - left_size) + i];
		}
		(*my_t_array_chunk_ptr) += left_size;
	}
	free(*t_array_ptr);
}

void pack_buffer(char ** buffer, Meta_Data *meta_data, int *const pos)
{
	*pos = 0;

	const int buffer_size = sizeof(int) * 3 + sizeof(double) * 2 +
		sizeof(double) * 3 * meta_data->num_of_points;

	(*buffer) = (char*)malloc(buffer_size);

	MPI_Pack(&(meta_data->num_of_points), 1, MPI_INT, (*buffer), buffer_size, pos, MPI_COMM_WORLD);
	MPI_Pack(&(meta_data->num_of_clusters), 1, MPI_INT, (*buffer), buffer_size, pos, MPI_COMM_WORLD);
	MPI_Pack(&(meta_data->time_delta), 1, MPI_DOUBLE, (*buffer), buffer_size, pos, MPI_COMM_WORLD);
	MPI_Pack(&(meta_data->T), 1, MPI_DOUBLE, (*buffer), buffer_size, pos, MPI_COMM_WORLD);
	MPI_Pack(&(meta_data->max_iterations), 1, MPI_INT, (*buffer), buffer_size, pos, MPI_COMM_WORLD);

	MPI_Pack((meta_data->vec_a), (meta_data->num_of_points), MPI_DOUBLE, (*buffer), buffer_size, pos, MPI_COMM_WORLD);
	MPI_Pack((meta_data->vec_b), (meta_data->num_of_points), MPI_DOUBLE, (*buffer), buffer_size, pos, MPI_COMM_WORLD);
	MPI_Pack((meta_data->vec_R), (meta_data->num_of_points), MPI_DOUBLE, (*buffer), buffer_size, pos, MPI_COMM_WORLD);
}

void unpack_buffer(char *buffer, Meta_Data *const meta_data, const int buffer_size,
	int *const pos)
{
	*pos = 0;
	MPI_Unpack(buffer, buffer_size, pos, &(meta_data->num_of_points), 1, MPI_INT, MPI_COMM_WORLD);
	MPI_Unpack(buffer, buffer_size, pos, &(meta_data->num_of_clusters), 1, MPI_INT, MPI_COMM_WORLD);
	MPI_Unpack(buffer, buffer_size, pos, &(meta_data->time_delta), 1, MPI_DOUBLE, MPI_COMM_WORLD);
	MPI_Unpack(buffer, buffer_size, pos, &(meta_data->T), 1, MPI_DOUBLE, MPI_COMM_WORLD);
	MPI_Unpack(buffer, buffer_size, pos, &(meta_data->max_iterations), 1, MPI_INT, MPI_COMM_WORLD);

	meta_data->vec_a = (double*)malloc(sizeof(double)*meta_data->num_of_points);
	meta_data->vec_b = (double*)malloc(sizeof(double)*meta_data->num_of_points);
	meta_data->vec_R = (double*)malloc(sizeof(double)*meta_data->num_of_points);

	MPI_Unpack(buffer, buffer_size, pos, (meta_data->vec_a), (meta_data->num_of_points), MPI_DOUBLE, MPI_COMM_WORLD);
	MPI_Unpack(buffer, buffer_size, pos, (meta_data->vec_b), (meta_data->num_of_points), MPI_DOUBLE, MPI_COMM_WORLD);
	MPI_Unpack(buffer, buffer_size, pos, (meta_data->vec_R), (meta_data->num_of_points), MPI_DOUBLE, MPI_COMM_WORLD);
}

void init_t_array(double **t_array, int *const t_array_size, int *const my_t_array_chunk,
	const int num_of_procs, const double time_delta, const double T)
{
	int i;
	double div_res = T / time_delta;//assumption the division yields an integer

	/*
	if (div_res != round(div_res))
	{
	printf("%d- init_t_array :: program", __LINE__);
	system("PAUSE");
	exit(1);
	}
	*/

	*t_array_size = 1 + int(div_res);//plus the zero time, division gives steps!
	(*t_array) = (double*)malloc((*t_array_size) * sizeof(double));

#pragma omp parallel for default(shared) private(i)
	for (i = 0; i < (*t_array_size); i++)
	{
		(*t_array)[i] = i*time_delta;
	}

	*my_t_array_chunk = (*t_array_size) / num_of_procs;
}

void init_points_centroids(Point **points, Centroid **centroids, const double current_t, const Meta_Data *const meta_data)
{
	int points_size = meta_data->num_of_points, centroid_size = meta_data->num_of_clusters, i;
	double a, b, R, T = meta_data->T;

	if(centroid_size>points_size)
	{
		printf("%d-init_points_centroids :: program", __LINE__);
		system("PAUSE");
		exit(1);
	}

#pragma omp parallel default(shared) private(i, a, b, R)
	{
#pragma omp for
		for(i=0 ; i<points_size; i++)
		{
			a = meta_data->vec_a[i];
			b = meta_data->vec_b[i];
			R = meta_data->vec_R[i];

			(*points)[i].isDummyPoint = 0;
			(*points)[i].my_index = i;
			(*points)[i].x = a + R*cos(2*PI*current_t/T);
			(*points)[i].y = b + R*sin(2*PI*current_t/T);
			(*points)[i].centroid_index = -1;
			(*points)[i].min_dis = INT_MAX * 1.0;
		}
#pragma omp for
		for(i=0 ; i<centroid_size; i++)
		{
			(*centroids)[i].my_index = i;
			(*centroids)[i].x = (*points)[i].x;
			(*centroids)[i].y = (*points)[i].y;
		}
	}
}

void calc_min_distance(
	const Meta_Data *const meta_data, 
	const double *const my_t_array, 
	const int my_t_array_size, 
	Result *my_result, const int my_rank)
{ 
	int points_size = meta_data->num_of_points;
	int centroids_size = meta_data->num_of_clusters;
	int max_iterations = meta_data->max_iterations;

	Point *points = (Point*)malloc(points_size * sizeof(Point));
	Centroid *centroids = (Centroid*)malloc(centroids_size * sizeof(Centroid));

	Point *dev_points = NULL;
	Centroid *dev_centroids = NULL;
	int *dev_centroids_size;

	double current_calculated_min_dis;
	my_result->centroids = (Centroid*)malloc(centroids_size * sizeof(Centroid));
	my_result->min_d = INT_MAX*1.0;
	my_result->t = -1.0;

	set_points_to_work_with_cuda(&points, &points_size);//makes sure there is an integer num of blocks
	alloc_params_for_cuda(&dev_points, points_size, &dev_centroids, centroids_size, &dev_centroids_size);
	k_mean_plus_init(centroids_size);

	//time_delta main loop
	//this loop does not use omp beacuse of the approach used to implement the do_k_mean_plus(...) function i.e. all cpu's participate in the calc!
	for(int i=0; i<my_t_array_size; i++)
	{
		init_points_centroids(&points, &centroids, my_t_array[i], meta_data);

		do_k_mean_plus(
			points, points_size, 
			centroids, centroids_size,
			dev_points, dev_centroids, dev_centroids_size,
			max_iterations, &current_calculated_min_dis);

		if(current_calculated_min_dis < my_result->min_d)
		{
			my_result->min_d = current_calculated_min_dis;
			my_result->t = my_t_array[i];
			memcpy(my_result->centroids, centroids, centroids_size*sizeof(Centroid));
		}

#ifdef DEBUG_LOCAL_RESULTS
		char file_path[100] = "D:\\ZZZ_Final_Project_VS_2010\\Project\\Project\\my_local_results\\";
		char my_rank_str[20];
		sprintf(my_rank_str, "%d", my_rank);
		strcat(my_rank_str,".txt");
		strcat(file_path, my_rank_str);

		FILE *output = fopen(file_path, "a");
		fprintf(output, "%lf %lf\n", my_t_array[i], current_calculated_min_dis);
		for(int i=0; i<centroids_size; i++)
		{
			fprintf(output, "x: %.3lf\ty: %.3lf\n", current_calculated_centroids[i].x, 
				current_calculated_centroids[i].y);
		}
		fprintf(output, "\n-------------------------------------------------------------\n");
		fclose(output);
#endif

	}

	k_mean_plus_free_init();
	free_params_for_cuda(dev_points, dev_centroids, dev_centroids_size);
	free(points);
	free(centroids);	
}

void set_points_to_work_with_cuda(Point **points_ptr, int *points_size_ptr)
{
	int current_points_size = *points_size_ptr;
	int max_thr_per_block = get_max_num_of_threads_per_block();
	int left_points = -1;

	//case: we dont have an integer number of blocks
	if( (left_points = (*points_size_ptr) % max_thr_per_block) != 0)
	{
		(*points_ptr) = (Point*)realloc((*points_ptr), sizeof(Point)*(current_points_size + (max_thr_per_block-left_points)));
		*points_size_ptr = current_points_size + (max_thr_per_block-left_points);

#pragma omp parallel for default(shared)
		for(int i = current_points_size; i<(*points_size_ptr); i++)
		{
			(*points_ptr)[i].isDummyPoint = 1;
		}
	}
}

void finding_the_absolute_min_dis(const int root, const int my_rank, Result *const my_result, const int num_of_procs, const int centroids_size)
{
	double recv_min_val = -1, recv_time = -1;
	double *recv_centroids_x_y = NULL, *send_centroids_x_y = NULL;

	//doing this logic, we could get different times!! for the same min dis if there is such...
	//add numprocs error or check for one machine!!!

	if(num_of_procs>=2)
	{
		if(my_rank == num_of_procs-1)
		{
			send_centroids_x_y = (double*)malloc(sizeof(double)*centroids_size*2);
			get_centroids_as_array(&send_centroids_x_y, centroids_size, my_result);

			MPI_Send(&(my_result->t), 1, MPI_DOUBLE, my_rank-1, 0, MPI_COMM_WORLD);
			MPI_Send(&(my_result->min_d), 1, MPI_DOUBLE, my_rank-1, 0, MPI_COMM_WORLD);
			MPI_Send(send_centroids_x_y, centroids_size*2, MPI_DOUBLE, 
				my_rank-1, 0, MPI_COMM_WORLD);

			free(send_centroids_x_y);
		}
		else if(my_rank == root)//assumption root has rank zero!
		{	
			recv_centroids_x_y = (double*)malloc(sizeof(double)*centroids_size*2);

			MPI_Recv(&recv_time, 1, MPI_DOUBLE, my_rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&recv_min_val, 1, MPI_DOUBLE, my_rank+1, 0, 
				MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(recv_centroids_x_y, centroids_size*2, MPI_DOUBLE, 
				my_rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if(recv_min_val <= my_result->min_d )
			{
				write_final_result_to_file(
					recv_time, 
					recv_min_val, 
					recv_centroids_x_y, 
					centroids_size);
			}
			else
			{
				send_centroids_x_y = (double*)malloc(sizeof(double)*centroids_size*2);

				get_centroids_as_array(&send_centroids_x_y, centroids_size, my_result);

				write_final_result_to_file(
					my_result->t, 
					my_result->min_d, 
					send_centroids_x_y, 
					centroids_size);

				free(send_centroids_x_y);
			}

			free(recv_centroids_x_y);
		}
		else
		{	
			recv_centroids_x_y = (double*)malloc(sizeof(double)*centroids_size*2);

			MPI_Recv(&recv_time, 1, MPI_DOUBLE, my_rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&recv_min_val, 1, MPI_DOUBLE, my_rank+1, 0, 
				MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(recv_centroids_x_y, centroids_size*2, 
				MPI_DOUBLE, my_rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if(recv_min_val <= my_result->min_d)
			{
				MPI_Send(&recv_time, 1, MPI_DOUBLE, my_rank-1, 0, MPI_COMM_WORLD);
				MPI_Send(&recv_min_val, 1, MPI_DOUBLE, my_rank-1, 0, MPI_COMM_WORLD);
				MPI_Send(recv_centroids_x_y, centroids_size*2, 
					MPI_DOUBLE, my_rank-1, 0, MPI_COMM_WORLD);
			}
			else
			{
				send_centroids_x_y = (double*)malloc(sizeof(double)*centroids_size*2);

				get_centroids_as_array(&send_centroids_x_y, centroids_size, my_result);

				MPI_Send(&(my_result->t), 1, MPI_DOUBLE, my_rank-1, 0, MPI_COMM_WORLD);
				MPI_Send(&(my_result->min_d), 1, MPI_DOUBLE, my_rank-1, 0, MPI_COMM_WORLD);
				MPI_Send(send_centroids_x_y, centroids_size*2, 
					MPI_DOUBLE, my_rank-1, 0, MPI_COMM_WORLD);

				free(send_centroids_x_y);
			}

			free(recv_centroids_x_y);
		}
	}
	else//num_of_procs<2 --> one machine army
	{
		send_centroids_x_y = (double*)malloc(sizeof(double)*centroids_size*2);

		get_centroids_as_array(&send_centroids_x_y, centroids_size, my_result);

		write_final_result_to_file(
			my_result->t, 
			my_result->min_d, 
			send_centroids_x_y, 
			centroids_size);

		free(send_centroids_x_y);
	}
}

void get_centroids_as_array(double **centroids_x_y_ptr, const int centroids_size, const Result *const my_result)
{
	int k = 0;
	for(int i=0; i<centroids_size; i++)
	{
		(*centroids_x_y_ptr)[k] = my_result->centroids[i].x;
		(*centroids_x_y_ptr)[k+1] = my_result->centroids[i].y;
		k+=2;
	}
}

