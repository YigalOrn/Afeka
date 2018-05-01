#pragma once

void participateInDebugPrintAsMatrix(
	const MPI_Comm* matComm,
	int* buff,
	const int numProcs,
	const int myRank,
	const int root,
	int localData,
	int buffStale);

void participateInDebugPrintAsList(
	const MPI_Comm* matComm,
	int* buff,
	const int numProcs,
	const int myRank,
	const int root,
	int localData,
	int buffStale);

#pragma once
