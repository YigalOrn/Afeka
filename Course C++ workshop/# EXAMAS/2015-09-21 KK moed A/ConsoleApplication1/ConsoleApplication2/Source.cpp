#include <iostream>
using namespace std;

class One 
{
protected:
	int x;

public:
	One(int x = 3) : x(x) { cout << "One::One x=" << x << endl; }
	One(const One& other) :x(other.x * 2) { cout << "One::One(copy) x=" << x << endl; }
	virtual ~One() { cout << "A::~A x=" << x << endl; }

	virtual void foo(const One& o) 
	{
		cout << "A::foo typeid(o)=" << typeid(o).name() + 6 << endl;
	}

	int getX() const { return x; }
};

class Two : public One 
{
	One o;
public:
	Two() { cout << "Two::Two\n"; }
	Two(const One& theOne) : o(theOne) 
	{
		cout << "Two::Two(one) theOne.x=" << theOne.getX() << endl;
	}
	~Two() 
	{
		x--;
		cout << "Two::~Two\n";
	}

	virtual void foo()
	{
		cout << "Two::foo o.x=" << x << endl;
		One::foo(o);
	}
};

void foo(One* o1) 
{
	One o2(5);
	o1->foo(o2);
}


int main() 
{
	void q789();
	void q1011();
	void q12();



	q789();
	system("pause");
	q1011();
	system("pause");
	q12();

	return 1;
}

void q789() 
{
	One o1(8);
	Two t1(o1);
	cout << "1------------------\n";
	foo(&o1);
	foo(&t1);
	cout << "2------------------\n";
}

void q1011() 
{
	One* po = new Two();
	One a1 = *po;
	cout << "------------------\n";

	po->foo(a1);
	delete po;
}

void q12()
{
	One* arr[3];

	arr[0] = new One();
	arr[1] = new Two(*arr[0]);
	arr[2] = new Two(*arr[1]);

	foo(arr[2]);

	for (int i = 0; i < 3; i++)
		delete arr[i];
}




