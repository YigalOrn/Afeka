#include <mpi.h>
#include <omp.h>
#include <time.h>
#include <iostream>
using namespace std;

#include "HistogramCUDA.h"
#include "HistogramOpenMP.h"

void do_A_work(int* dataArr, int& size, int*histoResultArr_CompA, int* histoResultArr_CompB, int bucketsSize, const int& CompB);
void do_B_work(int* dataArr, int& size, int* histoResultArr_CompB, int bucketsSize, const int& CompA);

#define DEBUG_FOR_SMALL_SIZE
#define DEBUG_FOR_BIG_SIZE

const int CompA = 0;
const int CompB = 1;


int main(int argc, char* argv[])
{
	int numProcs, myRank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

	/*
	Please see also attached word doc.
	CMD/CLI additional params are: original data array size, buckets size/interval
	e.g. 3689, 256
	*/
	if (numProcs != 2 || argc != 3)
	{
		printf("# Error: numProcs!=2 || argc!=3 #");
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	int size = atoi(argv[1]);
	int bucketsSize = atoi(argv[2]);

	int *dataArr = NULL;
	int *histoResultArr_CompA = NULL, *histoResultArr_CompB = NULL;

	//CompA : works with openMP
	if (myRank == CompA)
	{
		do_A_work(dataArr, size, histoResultArr_CompA, histoResultArr_CompB, bucketsSize, CompB);
	}
	//CompB : works with CUDA
	else
	{
		do_B_work(dataArr, size, histoResultArr_CompB, bucketsSize, CompA);
	}

	MPI_Finalize();
	return 0;
}//main

void do_A_work(int* dataArr, int& size, int*histoResultArr_CompA, int* histoResultArr_CompB, int bucketsSize, const int& CompB)
{
	int sendSize;
	double t1, t2;
	MPI_Request request;

	/*
	Boris, perhaps we didnt get it...
	but we are trying to implement the Principle of least privilege, this is said regarding the prototypes location.
	reagrding utility functions, we understand the concept you told us nevertheless for this assignment we only have only few so,
	we didnt make a nother utility .cpp for them.
	*/
	void createDataArray(int** dataArrPtr, const int size, const int interval);
	void printFinalHistoResult(int* histoResultArr_CompA, int bucketsSize, double runTime);
	void mergeResults(int* arr1, int* arr2, const int size);

	srand(time(NULL));
	createDataArray(&dataArr, size, bucketsSize);

#ifdef DEBUG_FOR_SMALL_SIZE
	if (size <= 50)
	{
		for (int i = 0;i < size;i++)
		{
			printf("%d, ", dataArr[i]);
			if ((i + 1) % 5 == 0)
				printf("\n");
		}
		printf("\n");
	}
#endif

	t1 = MPI_Wtime();

	//send CompB his portion of the original data
	sendSize = (size % 2 != 0) ? size / 2 + 1 : size / 2;
	MPI_Isend(&dataArr[size / 2], sendSize, MPI_INT, CompB, 0, MPI_COMM_WORLD, &request);

	//allocate histo result space for openMP on host, also will be used in the final merge opp!
	histoResultArr_CompA = new int[bucketsSize];

	//call openMP Histo with dataArr
	calcHistoOpenMP(dataArr, size / 2, histoResultArr_CompA, bucketsSize);

	//allocate histo result space, to store Comp_B final histo result 
	histoResultArr_CompB = new int[bucketsSize];

	//receive CompB histo result by CUDA, store it in histoResultArr_CompB 
	MPI_Recv(histoResultArr_CompB, bucketsSize, MPI_INT, CompB, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	//merge both results to one single buckets array
	mergeResults(histoResultArr_CompA, histoResultArr_CompB, bucketsSize);

	t2 = MPI_Wtime();

	//print final result
	printFinalHistoResult(histoResultArr_CompA, bucketsSize, t2 - t1);

	//free allocated memory
	delete[]dataArr;
	delete[]histoResultArr_CompA;
	delete[]histoResultArr_CompB;
}

void do_B_work(int* dataArr, int& size, int* histoResultArr_CompB, int bucketsSize, const int& CompA)
{
	MPI_Status status;
	MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
	MPI_Get_count(&status, MPI_INT, &size);
	dataArr = new int[size];
	MPI_Recv(dataArr, size, MPI_INT, CompA, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	//allocate histo result space for device on host 
	histoResultArr_CompB = new int[bucketsSize];

	//reset the previously allocated array
#pragma omp for schedule(static) nowait
	for (int i = 0;i < bucketsSize;i++)
		histoResultArr_CompB[i] = 0;

	
	//call CUDA Histo with the received dataArr i.e. CompB portion of the data
	calcHistoCuda(dataArr, size, histoResultArr_CompB, bucketsSize);

	MPI_Send(histoResultArr_CompB, bucketsSize, MPI_INT, CompA, 0, MPI_COMM_WORLD);

	//free allocated memory
	delete[]dataArr;
	delete[]histoResultArr_CompB;
}

void createDataArray(int** dataArrPtr, const int size, const int interval)
{
	(*dataArrPtr) = new int[size];
#pragma omp for schedule(static) nowait
	for (int i = 0;i < size;i++)
		(*dataArrPtr)[i] = rand() % interval;

#ifdef DEBUG_FOR_BIG_SIZE
	if (size >= 100000 && interval == 2)
	{
#pragma omp for schedule(static) nowait
		for (int i = 0;i < size;i++)
			(*dataArrPtr)[i] = 0;

		(*dataArrPtr)[0] = 1;
		(*dataArrPtr)[size - 5] = 1;

		printf("$ DEBUG Mode (*dataArrPtr)[0] = 1;\t(*dataArrPtr)[size - 5] = 1; $\n");
	}
#endif
}

void printFinalHistoResult(int* histoResultArr_CompA, int bucketsSize, double runTime)
{
	printf("### final result ###\n");
	printf("--read as value:count--\n");
	for (int i = 0;i < bucketsSize;i++)
	{
		printf("%d:%d, ", i, histoResultArr_CompA[i]);
		if ((i + 1) % 5 == 0)
			printf("\n");
	}
	printf("\n### runtime since CompA Isend to CompB: %f ###\n", runTime);
}

void mergeResults(int* arr1, int* arr2, const int size)
{
#pragma omp parallel for schedule(static)
	for (int i = 0;i < size;i++)
		arr1[i] += arr2[i];
}