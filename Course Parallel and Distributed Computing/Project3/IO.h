#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "MyStructs.h"


/*
*
*
*/
const char* const file_path = "D:\\#Data File Inputs#\\project_data_file_0.txt";

/*
*
*
*/
const char* const final_result_file_path = "D:\\#Data File Inputs#\\output_project_data_file_x.txt";

/*
*
*
*/
void parse_project_data_file(ProjectMetaData* const projectMetaDataPtr);

/*
*
*
*/
void write_res_to_file(const float t, const float q, const Centroid* const centroids, const int centroids_size);

/*
*
*
*/
void write_qm_not_found_to_file();