#include <iostream>//see exam for this line !, perhaps fails compilation.
using namespace std;


class A
{
protected:
	int j;
public:
	A(int k) : j(k)
	{
		cout << *this << ' ';
	}

	~A()
	{
		cout << *this << ' ';
	}

	A(const A &a)
	{
		j = a.j;

		cout << *this;
	}

	friend ostream & operator << (ostream &os, A &a)
	{
		return os << a.j << ' ';
	}
};


//#define Q1
//#define Q2
#define Q3


#ifdef Q1
class B : public A
{
public:
	B(A a) :A(a)
	{
		cout << *this << ' ';
	}
};
#endif

#ifdef Q2
class B : public A
{
public:
	B(int var) :A(var)
	{
		cout << *this << ' ';
	}
};
#endif

#ifdef Q3
class B : public A
{
public:
	B(const B &b) :A(b)
	{
		j = b.j;

		cout << *this << ' ';
	}
	friend ostream & operator << (ostream &os, B &b)
	{
		return os << b.j << ' ';
	}
};
#endif




void main()
{
	B obj(2);
}





