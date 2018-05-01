#include <iostream>
#include <typeinfo>
using namespace std;


//#define Q1
//#define Q2
//#define Q3
#define Q4




#ifdef Q1
class A
{
	int i;
	char c;
public:
	A(int j = 0)
	{
		i = j;
		cout << "A ctor\n";
	}
	~A()
	{
		cout << "dtor\n";
	}
};

template <class T>
class Tem
{
	T t;
public:
	Tem(const T &t1)
	{

		cout << "t=t1\n";
	}
};

void main()
{
	Tem<Tem<A> > t1, t2(t1);
}
#endif

#ifdef Q2
class A
{
	int *x;
	float *y;
public:
	A(int i, float f)
	{
		x = new int(i);
		y = new float(f);
	}
	~A()
	{
		delete x;
		delete y;
	}
	A(A & a)
	{
		x = a.x;
		y = a.y;
	}
	A operator + (int &i)
	{
		return A(*x + i, *y + i);
	}

};

void main()
{
	A obj = A(1, 2) + 7;
}
#endif

#ifdef Q3
class A
{
public:
	void print()
	{
		cout << "A\n";
	}
};

class B : public A
{

public:
	void print()
	{
		cout << "B\n";
	}
};

class C : public B
{

public:
	void print()
	{
		cout << "C\n";
	}
};


void main()
{
	A *pc = new C;

	cout << typeid(*pc).name();
}
#endif

#ifdef Q4
template <class S>
void print(S obj1 = 0, S obj2 = 0)
{
	cout << obj1 + obj2 << "\n";
}

void main()
{
	print(3, 5);
	print(3);
	print();//in KK template ppt
}
#endif


