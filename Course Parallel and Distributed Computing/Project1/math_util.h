#pragma once

#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14

double calc_norm(double x1, double y1, double x2, double y2);

/*
This function returns in curr_size the nearest power of 2.
e.g. if curr_size = 65 then the function returns curr_size = 128.
It is used in my parallel min-reduction function.
*/
void find_nearest_power_of_2(int *curr_size);

/*
Merly finds two integers numbers T and k such that k divides T.
k is the bounds given as function args.
k is returned a T is exchanged.
*/
int get_numerator_and_divisor_denominator_in_bounds(int *T_ptr, const int start, const int end);
