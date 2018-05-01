#include <iostream>
using namespace std;


class A
{
	int i;
	static int j;
public:
	A()
	{
		i = j;
	}
	static void operator [] (int val)
	{
		j = val;
	}
	~A()
	{
		cout << i;
	}
};

int A::j = 23;

void main()
{
	A obj;

	obj[0];

	A obj1;
}
