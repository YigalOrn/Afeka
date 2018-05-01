#pragma once

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
using namespace std;


void calcHistoCuda(int* dataArr, const int dataArrSize, int* const histoResultArr, const int histoResultArrSize);

void checkAndMakeDataDivisionCuda(const int max_num_thr_per_gpu, const int dataArrSize, int& num_thr, int& block_size, int& left_units);

void freeAllocatedMemoryCuda(int* dev_dataArr, int* dev_histoResultArr, int* dev_localHistoMat);

void malloc_copyCuda(int** dev_arr, const int dev_arr_size, int* host_arr);

void statusCuda(cudaError_t cudaStatus ,char* statusMessage);

