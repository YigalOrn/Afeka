#pragma once

#include <omp.h>
#include <iostream>
using namespace std;


void calcHistoOpenMP(int* dataArr, const int dataArrSize, int* const histoResultArr, const int histoResultArrSize);

void allocateLocalHistoMatOpenMP(int*** localHistoMat, const int bucketsSize);

void freeAllocatedMemoryOpenMP(int*** localHistoMat);

void createLocalHistoMatOpenMP(const int* const dataArr, const int dataArrSize, int** localHistoMat, const int bucketsSize);

void resetHistoArrayOpenMP(int* const histoResultArr, const int histoResultArrSize);

void mergeToFinalHistoArrOpenMP(int* const histoResultArr, const int bucketsSize, int const * const * const localHistoMat);
