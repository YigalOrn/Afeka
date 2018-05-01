#include <mpi.h>
#include <cmath>

#include "ShearSortHeader.h"
#include "OddEvenSortHeader.h"
#include "DirectionEnumHeader.h"

void participateInShearSort(
	const MPI_Comm* matComm, const int numProcs, const int myRank, int* localData)
{
	int maxSteps = caclMaxSteps(numProcs);

	for (int i = 0; i < maxSteps; i++)
	{
		if (i % 2 == 0)//sort all rows simultaneously!
		{
			participateInOddEvenSort(matComm, numProcs, myRank, localData, SORT_ROWS);
		}
		else //sort all cols as rows simultaneously!
		{
			participateInOddEvenSort(matComm, numProcs, myRank, localData, SORT_COLS);
		}
	}
}

int caclMaxSteps(const int& n)
{
	//this formula is taken from the lecture (pdf) presenting shear-sort
	//sqrt(n) + ceil(log2(n)) + 1;
	return (2 * ceil(log2(n)) + 1);
}