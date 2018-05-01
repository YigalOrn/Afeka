#pragma once

#include <omp.h>
#include <mpi.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_data_types.h"
#include "file_io.h"
#include "math_util.h"
#include "k_mean_parallel_algo.h"


/*
this function deallocates any previous mutual allocations
that were allocated in one point and used through all the program.
*/
void final_program_free(double *my_t_array, Meta_Data *meta_data_ptr, Result *my_result_ptr);

/*
root/master machine reads the input file in the format specified in the project 
specification document, this data is read into a self defined struct of type
Meta_Data.
the instance of this structure will be used by all machines through out 
the program execution SPMD style.
each machine gets the read information using collective MPI routines
and initializes her own copy of a Meta_Data instance.
*/
void get_meta_data(Meta_Data *meta_data_ptr, const int my_rank, const int root);

/*
after master uses the init_t_array(...) function, each machine participates in a collective MPI routine to get her chunk of time-t's that she will process. 
*/
void get_t_array_chunk(
	const Meta_Data *const meta_data_ptr,
	double **t_array_ptr, int *t_array_size_ptr,
	double **my_t_array_ptr, int *my_t_array_chunk_ptr, 
	const int my_rank, const int root, const int num_of_procs);

/*
the array of time-t's may not be divisible by the number of participating machines,
in this case the root will deduce it and recreate its own chunk of time-t's 
(memory and values) to include the first given time-t's and the left-over 
from the end of the general time-t's array.
*/
void check_t_array_left_overs(
	double** t_array_ptr, const int t_array_size,
	double** my_t_array_ptr, int *my_t_array_chunk_ptr, 
	const int num_of_procs);

/*
this function serves as a util function, it uses the MPI framework
to translate the data in the roots Meta_Data instance to a one big (packed) array
to be collectively broadcasted later on.
*/
void pack_buffer(char ** buffer, Meta_Data *meta_data, int *const pos);

/*
this function is also a utility function that does extactly the opposite from the
pack_buffer(...) function
*/
void unpack_buffer(char *buffer, Meta_Data *const meta_data, const int buffer_size, 
	int *const pos);

/*
this function uses the delta_time in meta_data do initialize the general array of
time-t's to be later distributed among all participating machines.
*/
void init_t_array(double **t_array, int *const t_array_size, int *const my_t_array_chunk, 
	const int num_of_procs, const double time_delta, const double T);

/*
this function is the heart of the project.
her job is to return the absulute min dis(along with other required data)
, absulute regarding her chunk of time-t's!!!
*/
void calc_min_distance(const Meta_Data *const meta_data, const double *const my_t_array, const int my_t_array_size, Result *my_result, const int my_rank);

/*
taking into regard the system parametrs in which the program will execute,
this function prepers the arrays that the program works with to accomplish 
its tasks. specifically it will inflate the relavant arrays (if there is a need to)
with dummy-points so the calculation done by using the CUDA framework will be effective as possible. 
*/
void set_points_to_work_with_cuda(Point **points_ptr, int *points_size_ptr);

/*
each machine has only its own initialized copy of the meta_data onstance.
in each step of the machines job it will calculated the data sets i.e. points and centroids in relation to the current time t.  
*/
void init_points_centroids(Point **points, Centroid **centroids, const double current_t, const Meta_Data *const meta_data);

/*
when each machine finishes her execution if the function calc_min_distance(...)
the program only has wanted data deduced from each machine chunk of time-t's!
this function than takes this "local results" and using MPI routines
collects the final wanted result(time-t, centroids, min dis) 
so at the end of the process the root has the wanted result.
*/
void finding_the_absolute_min_dis(const int root, const int my_rank, Result *const my_result, const int num_of_procs, const int centroids_size);

/*
this is a util function that takes an array of type Centroid and converts it to
an array of type double so the last could be sent using the MPI routines with no
effort.
*/
void get_centroids_as_array(double **centroids_x_y_ptr, const int centroids_size, const Result *const my_result);

