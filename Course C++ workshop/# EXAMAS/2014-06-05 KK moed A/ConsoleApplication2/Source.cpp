#include <iostream>
using namespace std;


class A
{
private:
	int *p1, *p2;
	static int num;
public:
	A(int param = 1) : p1(new int(param)), p2(p1)
	{
		num++;
	}

	A(const A& other) : p1(new int(*other.p1 + 1)), p2(other.p2) {}

	~A()
	{
		num--;
		cout << "In A::~A" << endl;
	}

	const A& operator=(const A& other)
	{
		if (this != &other)
		{
			p1 = other.p1;
			p2 = other.p2;
		}
		return *this;
	}

	const A& operator++()
	{
		(*p1)++;
		(*p2)--;

		return *this;
	}

	operator int&() { return *p1; }

	static int getNum() { return num; }

	friend ostream& operator<<(ostream& os, const A& obj)
	{
		return os << *obj.p1 << " " << *obj.p2;
	}
};

int A::num = 0;


class B
{
public:
	B(int x = 0)
	{
		A a(x);
	}

	~B()
	{
		cout << "In B::~B " << A::getNum() << endl;
	}

	static void foo(int& x)
	{
		x++;
	}
};



//#define Q8
#define Q9
//#define Q10
//#define Q11
//#define Q12
//#define Q13



#ifdef Q8
void main()
{
	A a1(7);
	A* a2 = new A(a1);

	cout << a1 << endl;
	cout << *a2 << endl;
}
#endif

#ifdef Q9
void main()
{
	B b1;

	A a1(3);
	A a2 = 4;
	A a3 = a2;
	a2 = a3;

	cout << a2 << endl;
}
#endif

#ifdef Q10
void main()
{
	A arr[3];

	for (int i = 0; i < 2; i++)
	{
		arr[i] = arr[i + 1];
		++arr[i];
	}

	for (int i = 0; i < 3; i++)
	{
		cout << arr[i] << endl;
	}
}
#endif

#ifdef Q11
void main()
{
	B b1;
	B b2(b1);
	B b3(2);

	b1 = b2;
}
#endif

#ifdef Q12
void main()
{
	{
		B* b1 = new B();
		B b2(*b1);

		delete b1;
		cout << A::getNum() << endl;
	}

	cout << A::getNum() << endl;
}
#endif

#ifdef Q13
void main()
{
	A a1(5);

	B::foo(a1);
	cout << a1 << endl;
}
#endif


