#include<iostream>
#include <typeinfo>
using namespace std;

template <class T>
class A
{

public:

	T* t;

	A(T& obj) :t(&obj)
	{
		cout << "A::ctor" << endl;
	}
};

class B
{

public:

	int x1;

	B(int x) :x1(x)
	{
		cout << "B::ctor" << endl;
	}
};

class C
{

public:

	A<B> a;

	C(B& b) : a(b)
	{
		cout << "C::ctor" << endl;
	}

	C(const C& otherC) : a(otherC.a)
	{
		cout << "C::copy-ctor" << endl;
	}

	//C(C&&) = delete;//move c'tor
	
};

int main(void)
{

	C c1(C(B(30)));

	/*
	//No the same !!!
	B b(30);
	C c(b);
	C c1(c);
	*/

	return 0;
}//main

