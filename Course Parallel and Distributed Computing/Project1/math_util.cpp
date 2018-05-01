#include "math_util.h"

double calc_norm(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

void find_nearest_power_of_2(int *curr_size)
{
	unsigned int v = *curr_size;

	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;

	*curr_size = v;//new size
}

int get_numerator_and_divisor_denominator_in_bounds(int *T_ptr, const int start, const int end)
{
	srand((unsigned int)time(NULL));

	int  k = start;
	*T_ptr =  rand();
	while(1)
	{
		while( (*T_ptr % k != 0) && (k < end) ){ k++; }

		if( (*T_ptr % k == 0) && (*T_ptr != k) )
		{ 
			break; 
		}
		else
		{
			*T_ptr =   rand();
			k=3;
		}
	}
	return k;
}

