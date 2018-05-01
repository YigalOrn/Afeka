#include <iostream>
#include <typeinfo>
using namespace std;


class A
{
	int a;
	int *pa;
public:
	A(int i) :a(i), pa(&a)
	{
		cout << a;
	}
	virtual ~A()
	{
		cout << *pa;
	}
	int *get()
	{
		return pa;
	}
};

class B : public A
{
	int *pb;
public:
	B(A obj) :A(obj), pb(obj.get() + 1)
	{
		cout << *(pb - 1);
	}
	~B()
	{
		cout << *(pb - 1);
	}
};


void print_me(A p)
{
	cout << typeid(p).name();
}

void main()
{
	int arr[] = { 1,2,4,5 };                                   # line (1)
		A *p = new B(A(sizeof(arr) / sizeof(int)));  # line (2)
		cout << typeid(*p).name();                        # line (3)
		print_me(*p);                                              # line(4)
}
