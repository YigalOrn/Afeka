#pragma once

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <omp.h>
#include <mpi.h>

#include "IO.h"
#include "MyStructs.h"
#include "Kernel.h"
#include "Kmeans.h"
#include "QM.h"

#define ROOT 0

/*
* debug for each rank its time slot according to prog logic
*/
//#define DEBUG_1

/*
* debug for each rank its answer as received by root 
*/
#define DEBUG_2

/*
* debug final answer rank
*/
//#define DEBUG_3


/*
*
*/
void free_node_meta_data(ProjectMetaData* projectMetaDataPtr, TimeData* timeDataPtr);

/*
*
*/
void stamp_count_time(const double* const t2Ptr);

/*
*
*/
void calc_time_arrays(
	const ProjectMetaData* const projectMetaData,
	TimeData* const timeDataArray,
	const int numprocs);

/*
*
*/
void send_meta_data(
	const int numprocs,
	ProjectMetaData* const projectMetaDataPtr,
	TimeData* const timeDataPtr);

/*
*
*/
void recv_meta_data(ProjectMetaData* const projectMetaDataPtr, TimeData* const timeDataPtr);

/*
*
*/
void start_project_task(const int rank, const int numprocs, ProjectMetaData* projectMetaDataPtr, const TimeData* const timeDataPtr);

/*
*
*/
Point* create_empty_points_array(ProjectMetaData* projectMetaDataPtr);

/*
*
*/
void init_points_and_centroids_for_this_time_round(
	const ProjectMetaData* const projectMetaDataPtr,
	Point *points, const int points_size,
	Centroid* centroids, const int centroids_size,
	const float t);

/*
*
*/
void createType(MPI_Datatype* SyncedAnswerMPITypePtr);

