#include <iostream>
using namespace std;

class A
{
	int i;
public:
	A(int j) :i(j)
	{}
	A operator+(A obj)//"this + obj"
	{
		return A(i + obj.i);
	}
	friend A operator+(A obj1, A obj2)
	{
		return A(obj1.i + obj2.i);
	}
};//A

void main()
{
	A a(3), b(5), c(0);
	c = a + b;
}//main