#include <mpi.h>
#include <iostream>
using namespace std;

#include "DebugPrintHeader.h"

void participateInDebugPrintAsMatrix(const MPI_Comm* matComm, int* buff, const int numProcs, const int myRank, const int root, int localData, int buffStale)
{
	if (!buffStale)
	{
		MPI_Gather(&localData, 1, MPI_INT, buff, 1, MPI_INT, root, *matComm);
	}
	/*
	after the above the process with rank root(same rank as in matComm! see mpi_cart_create)
	will have an array containing the localData of all the other processes.
	the wonderful thing is, each process will put his value in the buffer according to his
	rank in the matComm!!!.
	in the following code we will use this property to print the matrix topology nicely.
	*/

	if (myRank == root)
	{
		int matId;
		int coord[2];
		int size = sqrt(numProcs);
		printf("[rank,(coord[0],coord[1])] - localData\n");
		printf("##################################################\n");
		for (int i = size - 1; i >= 0; i--)
		{
			for (int j = 0; j < size; j++)
			{
				coord[0] = j;
				coord[1] = i;
				MPI_Cart_rank(*matComm, coord, &matId);
				if (j < size - 1)
				{
					printf("[%-3d,(%d,%d)] - %-3d,\t", matId, i, j, buff[matId]);
					fflush(stdout);
				}
				else
				{
					printf("[%-3d,(%d,%d)] - %-3d", matId, i, j, buff[matId]);
					fflush(stdout);
				}
			}//for_j
			printf("\n\n");
			fflush(stdout);
		}//for_i
		printf("##################################################\n");
	}
}

void participateInDebugPrintAsList(
	const MPI_Comm* matComm, int* buff, const int numProcs, const int myRank, const int root, int localData, int buffStale)
{
	if (!buffStale)
	{
		MPI_Gather(
			&localData, 1, MPI_INT,
			buff, 1, MPI_INT,
			root, *matComm);
	}
	/*
	after the above the process with rank root(same rank as in matComm! see mpi_cart_create)
	will have an array containing the localData of all the other processes.
	the wonderful thing is, each process will put his value in the buffer according to his
	rank in the matComm!!!.
	in the following code we will use this property to print the matrix topology nicely.
	*/

	if (myRank == root)
	{
		bool changeOrder = false;
		int matId;
		int coord[2];
		int size = sqrt(numProcs);
		printf("[rank,(coord[0],coord[1])] - localData\n");
		printf("##################################################\n");
		for (int i = size - 1; i >= 0; i--)
		{
			if (!changeOrder)
			{
				for (int j = 0; j < size; j++)
				{
					coord[0] = j;
					coord[1] = i;
					MPI_Cart_rank(*matComm, coord, &matId);
					printf("[%-3d,(%d,%d)] - %-3d\n", matId, i, j, buff[matId]);
					fflush(stdout);
				}
				changeOrder = true;
			}
			else
			{
				for (int j = size - 1; j >= 0; j--)
				{
					coord[0] = j;
					coord[1] = i;
					MPI_Cart_rank(*matComm, coord, &matId);
					printf("[%-3d,(%d,%d)] - %-3d\n", matId, i, j, buff[matId]);
					fflush(stdout);
				}
				changeOrder = false;
			}
		}
		printf("##################################################\n");
	}
}