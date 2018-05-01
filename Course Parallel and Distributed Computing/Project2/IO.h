#pragma once

#include "MyStructs.h"


/*
*
*
*/
const char* const file_path = "D:\\#Data File Inputs#\\project_data_file_1.txt";

/*
*
*
*/
const char* const final_result_file_path = "D:\\#Data File Inputs#\\output_project_data_file_x.txt";

/*
*
*
*/
void parse_project_data_file(ProjectMetaData* const projectMetaDataPtr, Point** pointsPtr);

/*
*
*
*/
void parse_point(FILE* const input, Point* const point, const int vector_size);

/*
*
*
*/
void debug_write_to_file(
	Point* points, const int num_of_points,
	const int vector_size,
	Centroid* centroids, const int num_of_centroids,
	const float* const meta_centroids_qualityEval,
	const int* const meta_centroids_num_of_memebrs,
	const float* const diameters_qualityEval);

/*
*
*
*/
void write_res_to_file(const int, const Centroid* const, const float, const int);