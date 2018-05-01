#include "HistogramOpenMP.h"


void calcHistoOpenMP(int* dataArr, const int dataArrSize, int* const histoResultArr, const int histoResultArrSize)
{
	int** localHistoMat = NULL;

	allocateLocalHistoMatOpenMP(&localHistoMat, histoResultArrSize);

	createLocalHistoMatOpenMP(dataArr, dataArrSize, localHistoMat, histoResultArrSize);

	resetHistoArrayOpenMP(histoResultArr, histoResultArrSize);

	mergeToFinalHistoArrOpenMP(histoResultArr, histoResultArrSize, localHistoMat);

	freeAllocatedMemoryOpenMP(&localHistoMat);
}

void allocateLocalHistoMatOpenMP(int*** localHistoMat, const int bucketsSize)
{
	int numThr;
#pragma omp parallel shared(numThr, localHistoMat, bucketsSize)
	{
		
#pragma omp single
		{
			numThr = omp_get_num_threads();
			(*localHistoMat) = new int*[numThr];
		}
		
#pragma omp for schedule(static) 
		for (int i = 0; i < numThr; i++)
		{
			(*localHistoMat)[i] = new int[bucketsSize];
		}
		
#pragma omp for schedule(static) 
		for (int i = 0;i < numThr;i++)
		{
			for (int j = 0;j < bucketsSize;j++)
			{
				(*localHistoMat)[i][j] = 0;
			}
		}
	}
}

void freeAllocatedMemoryOpenMP(int*** localHistoMat)
{
	int numThr;
#pragma omp parallel shared(localHistoMat, numThr)
	{
#pragma omp single 
		numThr = omp_get_num_threads();
#pragma omp for schedule(static) nowait 
		for (int i = 0; i < numThr; i++)
		{
			/*
			Boris remark:
			This will work in a parallel way only if the activated threads by OMP
			could be allocated each a kernel thread to actually free the allocated sapce on the under lying OS.
			*/
			delete[](*localHistoMat)[i];
		}
	}
	delete[](*localHistoMat);
}

void createLocalHistoMatOpenMP(const int* const dataArr, const int dataArrSize, int** localHistoMat, const int bucketsSize)
{
	int tid;
#pragma omp parallel  shared(dataArr, dataArrSize,localHistoMat, bucketsSize) private(tid)
	{
		tid = omp_get_thread_num();
#pragma omp for schedule(static) nowait 
		for (int i = 0; i < dataArrSize; i++)
		{
			localHistoMat[tid][dataArr[i]]++;
		}
	}
}

void resetHistoArrayOpenMP(int* const histoResultArr, const int histoResultArrSize)
{
#pragma omp parallel shared(histoResultArr, histoResultArrSize)
	{
#pragma omp for schedule(static) nowait  
		for (int i = 0;i < histoResultArrSize;i++)
			histoResultArr[i] = 0;
	}
}

void mergeToFinalHistoArrOpenMP(int* const histoResultArr, const int bucketsSize, int const * const * const localHistoMat)
{
	int numThr;
#pragma omp parallel shared(localHistoMat, histoResultArr, bucketsSize, numThr)
	{
#pragma omp single 
		numThr = omp_get_num_threads();
#pragma omp for schedule(static) nowait 
		for (int i = 0; i < bucketsSize; i++)
		{
			for (int j = 0; j < numThr; j++)
			{
				histoResultArr[i] += localHistoMat[j][i];
			}
		}
	}
}


