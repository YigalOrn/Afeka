#include <mpi.h>
#include <iostream>
#include <time.h>
#include <cmath>
using namespace std;

#include "DebugPrintHeader.h"
#include "ShearSortHeader.h"

/*
when not omitted a nice print will be in console other wise only sort run time will be displayed.
*/
#define DEBUG_PRINT

/*
when we first want to print the data scattered to other processes from the root,
because the root already has all the data already we don't need in the first debug print to
establish a communication between processes and root to get it again.
i use the following enum to distinguish between the need to get the sorted/new data from each process
or not.
*/
enum { STALE_BUFF, NOT_STALE_BUFF };

int main(int argc, char *argv[])
{
	int numProcs, myRank;
	MPI_Comm matComm;
	int dims[2], periods[2], reorder;
	int localData;//initial value from root/master
	int* dataToSort = NULL;//will hold initial values to be scattered
	double t1, t2;//for run time measure 
	const int root = 0;//define master

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

	double sqtrNumProcs = sqrt(numProcs);

	//checking if we can do the work with given numProcs, if not abort
	if (myRank == root)
	{
		double fractpart, intpart;
		fractpart = modf(sqtrNumProcs, &intpart);
		if (fractpart != 0)
		{
			cout << "# numProcs has no sqrt #" << endl;
			MPI_Abort(MPI_COMM_WORLD, 1);
		}
	}

	//-------------------------------
	//create and init new comm group, mesh/matrix(mat) layout, dims - sqrt(numProcs)*sqrt(numProcs)
	dims[0] = sqtrNumProcs;
	dims[1] = sqtrNumProcs;
	periods[0] = 0;
	periods[1] = 0;
	reorder = 0;//for easy printing. the rank in MPI_COMM_WORLD will be the same in matComm.
	MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &matComm);
	//-------------------------------

	//-------------------------------
	//init data
	if (myRank == root)
	{
		srand(time(NULL));
		dataToSort = new int[numProcs];//free allocation is at the end.
		for (int i = 0; i < numProcs; i++)
		{
			dataToSort[i] = rand() % 101;
		}
	}

	//distribute initial values to each process using scatter
	MPI_Scatter(dataToSort, 1, MPI_INT, &localData, 1, MPI_INT, root, MPI_COMM_WORLD);
	//-------------------------------

#ifdef DEBUG_PRINT
	participateInDebugPrintAsMatrix(
		&matComm, dataToSort, numProcs, myRank, root, localData, NOT_STALE_BUFF);

	participateInDebugPrintAsList(
		&matComm, dataToSort, numProcs, myRank, root, localData, NOT_STALE_BUFF);
#endif

	//-------------------------------
	//start stopwatch
	if (myRank == root) { t1 = MPI_Wtime(); }
	//sort -  using shear sort that uses oddEven sort
	participateInShearSort(&matComm, numProcs, myRank, &localData);
	//stop stopwatch
	if (myRank == root) { t2 = MPI_Wtime(); }
	//-------------------------------

#ifdef DEBUG_PRINT
	participateInDebugPrintAsMatrix(&matComm, dataToSort, numProcs, myRank, root, localData, STALE_BUFF);

	participateInDebugPrintAsList(&matComm, dataToSort, numProcs, myRank, root, localData, STALE_BUFF);
#endif

	//display run time and free allocated space
	if (myRank == root)
	{
		printf("@run time:\t %f@\n", t2 - t1);

		delete[]dataToSort;
	}

	MPI_Finalize();
	return 0;

}//main
