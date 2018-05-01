#include <stdlib.h>
#include <stdio.h>
#include <direct.h>
#include <time.h>
#include <string.h>

#include "IO.h"

void parse_project_data_file(ProjectMetaData* const projectMetaDataPtr, Point** pointsPtr) {

	int point_index = 0;
	int i = -1;
	FILE *input = fopen(file_path, "r");

	if (input == NULL) {
		printf("%d - parse_project_data_file :: IO.cpp\n", __LINE__);
		system("PAUSE");
		exit(0);
	}

	fscanf(input, "%d %d %d %d %f", 
		&(projectMetaDataPtr->num_of_points), 
		&(projectMetaDataPtr->vector_size),
		&(projectMetaDataPtr->max_clusters),
		&(projectMetaDataPtr->maxIter),
		&(projectMetaDataPtr->qm) );

	(*pointsPtr) = (Point*)malloc(sizeof(Point) * (projectMetaDataPtr->num_of_points) );

	if ((*pointsPtr) == NULL) {
		printf("%d - parse_project_data_file :: IO.cpp\n", __LINE__);
		system("PAUSE");
		exit(1);
	}

#pragma omp parallel for \
	default(shared) private(i) \
	schedule(static)
	for (i = 0; i < (projectMetaDataPtr->num_of_points); i++) {
		(*pointsPtr)[i].myCentroidIndex = -1;
		(*pointsPtr)[i].isDummyPoint = 0;
	}

	while (!feof(input) && point_index < (projectMetaDataPtr->num_of_points)) {
		parse_point(input, &(*pointsPtr)[point_index], (projectMetaDataPtr->vector_size));
		++point_index;
	}
	fclose(input);
}

void parse_point(FILE* const input, Point* const point, const int vector_size) {

	static char str[6];
	static int i;

	fscanf(input, "%s", str);
	for (i = 0; i < vector_size; i++) {
		fscanf(input, "%f", &(point->vector[i]));
	}
}

void debug_write_to_file(
	Point* points, const int num_of_points,
	const int vector_size,
	Centroid* centroids, const int num_of_centroids,
	const float* const meta_centroids_qualityEval,
	const int* const meta_centroids_num_of_memebrs,
	const float* const diameters_qualityEval) {

	static int ctr = 0;

	char buff1[20];
	char buff2[80] = "D:/#ProjectDebug#/clusters";
	itoa(num_of_centroids, buff1, 10);

	if (ctr == 0) {
		// create root dir
		char rootDir[80] = "D:/#ProjectDebug#";
		_mkdir(rootDir);
		++ctr;
	}

	strcat(buff2, buff1);
	_mkdir(buff2);

	strcat(buff2, "/data.txt");

	FILE *output = fopen(buff2, "w");

	for (int i = 0; i < num_of_points; ++i)
	{
		if (points[i].isDummyPoint != 1) {
			fprintf(output, "Point%d   ", i + 1);
			fprintf(output, "%d   ", points[i].myCentroidIndex);
			for (int j = 0; j < vector_size; ++j)
			{
				fprintf(output, "%.2f ", points[i].vector[j]);
			}
			fprintf(output, "\n");
		}
	}

	fprintf(output, "\n\n------------------------------------------------------------------------------------------\n\n");

	for (int i = 0; i < num_of_centroids; ++i)
	{
		fprintf(output, "Centroid%d ", i + 1);
		for (int j = 0; j < vector_size; ++j)
		{
			fprintf(output, "%.2f ", centroids[i].vector[j]);
		}
		fprintf(output, "\n");
	}

	fclose(output);
}

void write_res_to_file(const int num_of_centroids, const Centroid* const centroids, const float q, const int vector_size) {

	FILE *output = fopen(final_result_file_path, "w");

	fprintf(output, "K=%d\tq=%.2f\n", num_of_centroids, q);

	for (int i = 0; i < num_of_centroids; i++)
	{

		fprintf(output, "C%d  ", i + 1);
		for (int j = 0; j < vector_size; j++)
		{
			fprintf(output, "%.2f ", centroids[i].vector[j]);
		}
		fprintf(output, "\n");
	}
	fclose(output);
}