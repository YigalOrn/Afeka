#pragma once

void participateInShearSort(
	const MPI_Comm* matComm,
	const int numProcs,
	const int myRank,
	int* localData
);

int caclMaxSteps(const int& n);

