#include <iostream>
using namespace std;

class A
{
	int i;
public:
	A(int j) :i(j)
	{}
};//A

class B
{
protected:
	A *ptr;
public:
	B(const B &b) : ptr(b.ptr)
	{
		cout << "cc\n";
	}
};//B

void main()
{
	B B1;
	B LB(B1);
	cout << "main\n";
}//main
