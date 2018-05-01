#include <iostream>
using namespace std;

class A
{
	int i;
public:
	A(int j) :i(j)
	{
		//cout << "A::A" << endl;
	}
};//A

class B : public A
{
public:
	B(int j) : A(j)
	{}
};//B

class C : public A
{
public:
	C(int j) :A(j)
	{}
};//C

class D : public B, public C
{
public:
	D(int j) :B(j), C(j)/*C(999)*/
	{}
};//D

class E : public B
{
public:
	E(int j) :B(j)
	{}
};//E


void main()
{
	D d(2);//interesting case study for KK ppt 07
	E e(3);

	A a1 = d;//debug shows d actually has 2 base classes of type A
	A a2 = e;//copy c'tor : a method that expects a base type parameter gets a derived class parameter, is OK

}//main


