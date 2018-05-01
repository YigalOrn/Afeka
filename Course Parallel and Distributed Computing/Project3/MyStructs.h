#pragma once

/*
* this const is only a privilege so we could use MPI type create(serizalization)
* there is no trade off here only unused space 
*/
#define MAX_CLUSTERS 50

struct ProjectMetaData {
	int N, K, LIMIT;
	float QM, T, dT, *X, *Y, *Vx, *Vy;
} typedef ProjectMetaData;

struct TimeData {
	float* time_array;
	unsigned int arraySize;
} typedef TimeData;

struct Centroid {
	float x, y;
	int my_index;
} typedef Centroid;

struct Point {
	float x, y;
	int myCentroidIndex;
	float minDisFromCentroid;
	unsigned int isDummyPoint : 1;// using bit fields
} typedef Point;

struct SyncedAnswer {
	Centroid centroids[MAX_CLUSTERS];
	int arraySize;
	int notSyncedAnyMore;// will give root indication if the node is still relevant when synced
	float qm;
	float t;
}typedef SyncedAnswer;

