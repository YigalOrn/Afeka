#include <mpi.h>
#include <cmath>

#include "OddEvenSortHeader.h"
#include "DirectionEnumHeader.h"

void participateInOddEvenSort(
	const MPI_Comm* matComm, const int numProcs, const int myRank, int* localData, const int sortRows)
{
	int coord[2];
	int leftNeighbor, rightNeighbor, bottomNeighbor, topNeighbor;
	int sortOrder;
	static int steps = sqrt(numProcs);

	if (sortRows == SORT_ROWS)//setup oddEven sort on rows params  
	{
		MPI_Cart_shift(*matComm, 0, 1, &leftNeighbor, &rightNeighbor);
		MPI_Cart_coords(*matComm, myRank, 2, coord);

		//snake like sorts order
		//the term regards the shear-sort matrix topology
		if (steps % 2 == 0)
		{
			if (coord[1] % 2 != 0) { sortOrder = INCREASING; }
			else { sortOrder = DECREASING; }
		}
		else
		{
			if (coord[1] % 2 != 0) { sortOrder = DECREASING; }
			else { sortOrder = INCREASING; }
		}

		doOddEvenSort(matComm, steps, coord[0], leftNeighbor, rightNeighbor, localData, sortOrder);
	}
	else //setup oddEven sort on cols as rows params 
	{
		/*
		we logically treat leftNeighbor and rightNeighbor
		as bottom neighbor and top neighbor
		*/
		MPI_Cart_shift(*matComm, 1, 1, &bottomNeighbor, &topNeighbor);
		MPI_Cart_coords(*matComm, myRank, 2, coord);
		sortOrder = DECREASING;
		doOddEvenSort(matComm, steps, coord[1], bottomNeighbor, topNeighbor, localData, sortOrder);
	}
}

/*
one param that is not self explanatory is - checkCoord.
checkCoord is either - coord[0] or coord[1] defined in the setup phase above.
this param is used to check processes row/column as row coords boundary in the matrix topology.

previousNeighbor and nextNeighbor are generic names for - left/right/bottom/top neighbor
in the matrix topology. also defined in the setup phase for each process according the appropriate terms.

localData is the initial number given to each process by the root using scatter.
the value of this var should be changed as the sort goes on.
upon finishing the sort each process should have in this var a "sorted value" i.e. a value that when
we look at the matrix topology in a snake order we will have a sorted list composite from the
initial scattered values.

steps is the number of rows in the matrix topology.

sortOrder indicates whether the sort of a single row should be in increased or decreased order.
*/
void doOddEvenSort(const MPI_Comm* matComm, const int steps, const int checkCoord, const int previousNeighbor, const int nextNeighbor, int* localData, const int sortOrder)
{
	//actual odd-even transposition sort
	for (int i = 0; i < steps; i++)
	{
		if (i % 2 == 0)//even line
		{
			doEvenLine(matComm, steps, checkCoord, previousNeighbor, nextNeighbor, localData, sortOrder);
		}
		else//odd line 
		{
			doOddLine(matComm, steps, checkCoord, previousNeighbor, nextNeighbor, localData, sortOrder);
		}
	}//for
}

void doEvenLine(const MPI_Comm* matComm, const int steps, const int checkCoord, const int previousNeighbor, const int nextNeighbor, int* localData, const int sortOrder)
{
	int localRecvData, dataToSend;

	if (checkCoord % 2 != 0)
	{
		MPI_Sendrecv(localData, 1, MPI_INT, previousNeighbor, 0, &localRecvData, 1, MPI_INT, previousNeighbor, 0, *matComm, MPI_STATUSES_IGNORE);

		if (*localData != localRecvData) { *localData = localRecvData; }
	}
	else if (nextNeighbor != ENDLINE)
	{
		MPI_Recv(&localRecvData, 1, MPI_INT, nextNeighbor, 0, *matComm, MPI_STATUS_IGNORE);

		if (sortOrder == INCREASING)//sort increasing 
		{
			dataToSend = getMax(localRecvData, *localData);
		}
		else//sort decreasing 
		{
			dataToSend = getMin(localRecvData, *localData);
		}

		if (*localData == dataToSend) { *localData = localRecvData; }

		MPI_Send(&dataToSend, 1, MPI_INT, nextNeighbor, 0, *matComm);
	}
}

void doOddLine(const MPI_Comm* matComm, const int steps, const int checkCoord, const int previousNeighbor, const int nextNeighbor, int* localData, const int sortOrder)
{
	int localRecvData, dataToSend;

	//work on mesh!
	if ((checkCoord % 2 != 0) && (nextNeighbor != ENDLINE))
	{
		MPI_Sendrecv(localData, 1, MPI_INT, nextNeighbor, 0, &localRecvData, 1, MPI_INT, nextNeighbor, 0,
			*matComm, MPI_STATUSES_IGNORE);

		if (*localData != localRecvData) { *localData = localRecvData; }
	}
	else if ((checkCoord % 2 == 0) && (checkCoord != 0))
	{
		MPI_Recv(&localRecvData, 1, MPI_INT, previousNeighbor, 0, *matComm, MPI_STATUS_IGNORE);

		if (sortOrder == INCREASING)//sort increasing  
		{
			dataToSend = getMin(localRecvData, *localData);
		}
		else//sort decreasing  
		{
			dataToSend = getMax(localRecvData, *localData);
		}

		if (*localData == dataToSend) { *localData = localRecvData; }

		MPI_Send(&dataToSend, 1, MPI_INT, previousNeighbor, 0, *matComm);
	}
}

int getMax(const int& a, const int& b)
{
	if (a < b) return b;
	else return a;
}

int getMin(const int& a, const int& b)
{
	if (a < b) return a;
	else return b;
}

