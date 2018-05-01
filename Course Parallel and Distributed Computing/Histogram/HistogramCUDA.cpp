#include "HistogramCUDA.h"
#include "CUDA_GateWay.h"


void calcHistoCuda(int* dataArr, const int dataArrSize, int* const histoResultArr, const int histoResultArrSize)
{
	int* dev_dataArr = NULL;
	int* dev_histoResultArr = NULL;
	int* dev_localHistoMat = NULL;

	//-----------------
	//init params for program flow and kernel lunches
	struct cudaDeviceProp properties;
	int max_num_thr_per_gpu = 0;
	int num_thr = 0, block_size = 0, left_units = 0;

	cudaGetDeviceProperties(&properties, 0);
	max_num_thr_per_gpu = properties.maxThreadsPerBlock;

	statusCuda(
		cudaSetDevice(0),
		"cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?\n");
	//-----------------

	checkAndMakeDataDivisionCuda(max_num_thr_per_gpu, dataArrSize, num_thr, block_size, left_units);

	statusCuda(
		cudaMalloc((void**)&dev_localHistoMat, num_thr * histoResultArrSize * sizeof(int)), 
		"cudaMalloc failed! for localHistoMat\n");
	
	malloc_copyCuda(&dev_dataArr, dataArrSize, dataArr);

	createLocalHistoMatCuda(dev_dataArr, dev_localHistoMat, block_size, left_units, num_thr, histoResultArrSize, dataArrSize);
	
	statusCuda(
		cudaDeviceSynchronize(), 
		"cudaDeviceSynchronize returned error code %d after launching CUDA_createLocalHistoMat_KernelCall!\n");
	
	malloc_copyCuda(&dev_histoResultArr, histoResultArrSize, histoResultArr);

	mergeToFinalHistoArrCuda(dev_histoResultArr, dev_localHistoMat, histoResultArr, num_thr, histoResultArrSize);

	statusCuda(
		cudaDeviceSynchronize() ,
		"cudaDeviceSynchronize returned error code %d after launching CUDA_mergeToFinalHistoArr_KernelCall!\n");

	statusCuda(
		cudaMemcpy(histoResultArr, dev_histoResultArr, histoResultArrSize * sizeof(int), cudaMemcpyDeviceToHost),
		"cudaMemcpy failed! after CUDA_mergeToFinalHistoArr_KernelCall\n");

	freeAllocatedMemoryCuda(dev_dataArr, dev_histoResultArr, dev_localHistoMat);
}

void checkAndMakeDataDivisionCuda(const int max_num_thr_per_gpu, const int dataArrSize, int& num_thr, int& block_size, int& left_units)
{
	//each thr gets one data unit
	if (max_num_thr_per_gpu >= dataArrSize)
	{
		num_thr = dataArrSize;
		block_size = 1;
	}
	//each thr will get a chunk of data + left over data will be proccesed also
	else
	{
		num_thr = max_num_thr_per_gpu;

		if (dataArrSize%max_num_thr_per_gpu == 0)
		{
			block_size = dataArrSize / num_thr;
		}
		else
		{
			block_size = dataArrSize / num_thr;//each thr will get a block to work on
			left_units = dataArrSize%num_thr;//the left over data will be distributed again in the cu file among left_unit threads
		}
	}
}

void freeAllocatedMemoryCuda(int* dev_dataArr, int* dev_histoResultArr, int* dev_localHistoMat)
{
	cudaFree(dev_dataArr);
	cudaFree(dev_histoResultArr);
	cudaFree(dev_localHistoMat);
}

void malloc_copyCuda(int** dev_arr, const int dev_arr_size, int* host_arr)
{
	statusCuda(
		cudaMalloc((void**)dev_arr, dev_arr_size * sizeof(int)), 
		"cudaMalloc failed! in CUDA_malloc_copy\n");
	
	statusCuda(
		cudaMemcpy(*dev_arr, host_arr, dev_arr_size * sizeof(int), cudaMemcpyHostToDevice),
		"cudaMemcpy failed! in CUDA_malloc_copy\n");	
}

void statusCuda(cudaError_t cudaStatus ,char* statusMessage)
{
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, statusMessage, cudaStatus);
	}
}
