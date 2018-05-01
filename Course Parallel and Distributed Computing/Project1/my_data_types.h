#pragma once

struct Meta_Data
{
	int num_of_points;
	int num_of_clusters;
	double time_delta;
	double T;
	int max_iterations;
	double *vec_a;
	double *vec_b;
	double *vec_R;
}typedef Meta_Data;

struct Point
{
	int isDummyPoint;//help field used to utilize CUDA calcs.
	int my_index;
	int centroid_index;
	double x;
	double y;
	double min_dis;
}typedef Point;

struct Centroid
{
	int my_index;
	double x;
	double y;
}typedef Centroid;


/*
This structure is used in each iteration where a full k mean iteration is done.
It helps to hold partial calculated data in each full k mean iteration, 
finally this structure is used to pass the final result to the Master machine. 
*/
struct Result
{
	double min_d;
	double t;
	Centroid *centroids;
}typedef Result;