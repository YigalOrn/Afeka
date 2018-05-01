#pragma once

#include "ProjectConstants.h"

/*
*
* */
struct Centroid {
	float vector[VEC_SIZE];
} typedef Centroid;

/*
*
* */
struct Point {
	float vector[VEC_SIZE]; 
	int myCentroidIndex;
	float minDis;
	int isDummyPoint;
} typedef Point;

/*
*
* */
struct ProjectMetaData {
	int num_of_points;
	int vector_size;
	int max_clusters;
	int maxIter;
	float qm;
}typedef ProjectMetaData;

/*
*
* */
struct NumberOfClustersSet {
	int numberOfClustersSet[MAX_CLUSTERS];
	int arraySize;
}typedef NumberOfClustersSet;

/*
*
* */
struct SyncedAnswer {
	Centroid centroids[MAX_CLUSTERS];
	int arraySize;
	int notSyncedAnyMore;// will give root indication if the node is still relevant when synced
	float qm;
}typedef SyncedAnswer;

