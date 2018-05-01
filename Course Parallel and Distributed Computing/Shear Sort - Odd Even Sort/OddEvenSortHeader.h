#pragma once

enum { ENDLINE = -1, INCREASING, DECREASING };

void participateInOddEvenSort(
	const MPI_Comm* matComm,
	const int numProcs,
	const int myRank,
	int* localData,
	const int sortRows
);

void doOddEvenSort(
	const MPI_Comm* matComm,
	const int steps,
	const int checkCoord,
	const int previousNeighbor, const int nextNeighbor,
	int* localData,
	const int sortOrder);

void doEvenLine(
	const MPI_Comm* matComm,
	const int steps,
	const int checkCoord,
	const int previousNeighbor, const int nextNeighbor,
	int* localData,
	const int sortOrder);

void doOddLine(
	const MPI_Comm* matComm,
	const int steps,
	const int checkCoord,
	const int previousNeighbor, const int nextNeighbor,
	int* localData,
	const int sortOrder);

int getMax(const int& a, const int& b);

int getMin(const int& a, const int& b);







