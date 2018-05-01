#include <iostream>
using namespace std;

#include "Set.h"


int main(void)
{

	Set s1;

	for (register int i = 0; i <= 100; i++)
	{
		s1 += i;
	}
	//cout << s1 << endl;

	for (register int i = 0, j = s1.getCurrentSize()-1; i < s1.getCurrentSize(); i++, j--)
	{
		s1[i] = j;
	}

	cout << s1 << endl;

	return 0;
}
