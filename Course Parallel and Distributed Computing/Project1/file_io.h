#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "math_util.h"
#include "my_data_types.h"

/*
This string specifies the full path to the input file i.e. the file 
from wich we should read the initial data for the program.
*/
const char *const file_path = 
"D:\\ZZZ_Final_Project_VS_2010\\Project\\Project\\meta_data_format_file.txt";

/*
Accordingly this string specifies the full path to the file where the final results should be written.
*/
const char *const final_result_file_path = 
"D:\\ZZZ_Final_Project_VS_2010\\Project\\Project\\final_result_file.txt";


/*
This function creates random meta data and 
writes it to an input file that can be used by this the program.
The new created input file has the format given in 
the project specification document. 
*/
void create_project_format_file();

/*
This is a help function.
The function create_project_format_file() uses this function to 
create random data for an input file.
This function finds an upper bound T and a divisor such that the division is
an integer.
*/
void init_time_interval_params(int *T_ptr, int *time_delta_ptr);

/*
This function reads any file in the format specified in the project specification document.
It initializes a help structure of the type Meta_Data.
After it is done the strucure of type Meta_Data will hold all 
needed data to perform the required work.
*/
void read_project_format_file(Meta_Data *meta_data_ptr);

/*
This function simply write the passed final results of the program as
reqeusted in the project specification document. 
*/
void write_final_result_to_file(const double time, const double dis, const double *const centroids_x_y, const int centroid_size);

