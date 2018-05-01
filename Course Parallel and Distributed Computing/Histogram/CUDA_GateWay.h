#pragma once

#include "cuda_runtime.h"
#include "device_launch_parameters.h"


void createLocalHistoMatCuda(int* dev_dataArr, int* dev_localHistoMat, int block_size, int left_units, int num_thr, int bucketsSize, int dataArrSize);

void mergeToFinalHistoArrCuda(int* dev_histoResultArr, int* dev_localHistoMat, int* histoResultArr, int num_thr, int histoResultArrSize);
