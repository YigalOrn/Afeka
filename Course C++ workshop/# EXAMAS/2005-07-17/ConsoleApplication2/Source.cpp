#include <iostream>
using namespace std;

class A
{
	int l;
	char *n;
public:
	A(int i) : l(i), n(new char[l])
	{}
	char &f(int i)
	{
		if (i >= 0 && i<l)
			return n[i];
		else
			throw A(2);
	}
	~A()
	{
		delete[] n;
	}
};

void main()
{
	A first(1), second(2);
	try {
		cout << first.f(0) << second.f(4);
	}
	catch (A &m)
	{
		m.f(2);
	}
}
