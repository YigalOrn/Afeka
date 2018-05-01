#include "CUDA_GateWay.h"


__global__ 
	void resetHistoMat(int* dev_histoMat, int bucketsSize)
{
	//reset each thr histo space before use
	for(int i=0;i<bucketsSize;i++)
	{
		dev_histoMat[threadIdx.x*bucketsSize+i] = 0;
	}
}

__global__ 
	void calcHisto(int* dev_dataArr, int* dev_histoMat, int blockSize, int bucketsSize)
{
	//each thread makes his own histo using his chunk of data
	for(int i=0; i<blockSize;i++)
	{
		dev_histoMat[ (threadIdx.x*bucketsSize) + (dev_dataArr[threadIdx.x*blockSize+i]) ] ++; 
	}
}

__global__ 
	void gatherToOne(int* dev_ResultHisto,int* dev_histoMat, int num_thr, int bucketsSize)
{
	for(int i=0;i<num_thr;i++)
	{
		dev_ResultHisto[threadIdx.x] +=dev_histoMat[threadIdx.x+i*bucketsSize];
	}
}

void createLocalHistoMatCuda(int* dev_dataArr, int* dev_localHistoMat, int block_size, int left_units, int num_thr, int bucketsSize, int dataArrSize)
{
	resetHistoMat<<<1, num_thr>>>(dev_localHistoMat, bucketsSize);

	//sync

	calcHisto<<<1, num_thr>>>(dev_dataArr, dev_localHistoMat, block_size, bucketsSize);

	if(left_units != 0)
	{

		//sync

		num_thr = left_units;
		block_size = 1;
		int startIndex = dataArrSize-left_units;
		calcHisto<<<1, num_thr>>>(&dev_dataArr[startIndex], dev_localHistoMat, block_size, bucketsSize);
	}
}

void mergeToFinalHistoArrCuda(int* dev_histoResultArr, int* dev_localHistoMat, int* histoResultArr, int num_thr, int histoResultArrSize)
{
	gatherToOne<<<1, histoResultArrSize>>>(dev_histoResultArr, dev_localHistoMat, num_thr, histoResultArrSize);
}

