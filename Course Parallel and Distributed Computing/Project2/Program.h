#pragma once

void createTypes1(MPI_Datatype*, MPI_Datatype*, MPI_Datatype*);

void createTypes2(MPI_Datatype*);

void start_project_procedure(const int, const int, const int, ProjectMetaData* const, Point*, const NumberOfClustersSet* const);

void set_centroids(Centroid**, const int, Point* const, const int);

void kmean(Point*, const int, Centroid* const, const int, const int, const int, float* const, int* const);

void zero_meta_data_structures(const int, const int, float* const, int* const);

void count_and_sum_after_classification_by_norm(const Point * const, const int, const int, const int, float* const, int* const);

unsigned int check_centroids_for_changes(float*, int*, Centroid *, const int, const int);

float evaluateQuality(Point* const, const int, Centroid* const, const int, const int, const int* const, float* const, Point* const, float* const);

void calc_distances_between_centroids(const Centroid* const, const int, float* const, const int);

void calc_diameter_for_each_cluster(Point* const, const int, const int, const int, const int* const, Point* const, float* const);

int sortPointsByCentroidIndex(const void*, const void*);