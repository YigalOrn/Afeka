#include <iostream>
using namespace std;


template <class T>
T operator + (const T &t1, const T &t2)
{
	return t1 * t2;
}

class Int
{
	int i;
public:
	Int(int j) :i(j)
	{}
};

int main()
{
	Int a(1), b(2);

	b = a + b;
	return 0;
}
