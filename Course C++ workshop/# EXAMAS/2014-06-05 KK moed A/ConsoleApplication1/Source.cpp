#include <iostream>
using namespace std;

template <class T>
class A
{
private:
	static T* ptr;
	static int num;

public:
	A(const T& obj)
	{
		if (num == 0)
		{
			ptr = new T(obj);
		}
		num++;
	}

	~A()
	{
		if (--num == 0)
		{
			delete ptr;
		}
		cout << "In A::~A\n";
	}

	void print() const { cout << "*ptr=" << *ptr << ", num=" << num << endl; }
	T* getT() { return ptr; }
};

template <class T>
T* A<T>::ptr = NULL;

template <class T>
int A<T>::num = 0;


class B
{
	static int num;
public:
	B(int x = 1)
	{
		num = x;
	}

	~B()
	{
		num--;
		cout << "In B::~B\n";
	}

	friend ostream& operator<<(ostream& os, const B& b)
	{
		return os << b.num << " ";
	}

	void print() const { cout << "num: " << num << endl; }

	B& operator++(int)
	{
		++num;
		return *this;
	}

	static int getNum() { return num; }
};

int B::num = 0;


class C
{
	A<B> var;

public:
	C(const B& b) : var(b) { cout << "DEBUG" << endl; }
	C(const C& other) :var(other.var)
	{
		cout << "DEBUG" << endl;
		(*var.getT())++;
	}

	~C() { cout << "In C::~C\n"; }

	void print() const { var.print(); }
};

//#define Q1
//#define Q2
//#define Q3
//#define Q4
//#define Q5
//#define Q6
#define Q7



#ifdef Q1
void main()
{
	B b(2);
	A<B> t1(b);
	A<B> t2(5);
	t1.print();
	(*t2.getT())++;
	b.print();
}
#endif

#ifdef Q2
void main()
{
	{
		B arr[3];
		for (int i = 0; i < 3; i++)
			arr[i]++;

		for (int i = 0; i < 3; i++)
			arr[i].print();
		cout << B::getNum() << endl;
	}
	cout << B::getNum() << endl;
}
#endif

#ifdef Q3
void main()
{
	double d = 1.1;
	A<double> a1(d);
	A<double> a2(d);
	a1.print();
	a2.print();
}
#endif

#ifdef Q4
void main()
{
	A<int> a1(5);
	A<double> a2(5.5);
	a1.print();
	a2.print();
}
#endif

#ifdef Q5
void main()
{
	double d = 1.1;
	A<double> a1(d);
	A<double> a2(d);
	cout << *a1.getT() << endl;
	*a1.getT() = 2.2;
	cout << *a1.getT() << endl;
}
#endif

#ifdef Q6
void main()
{
	C c1(B(30));
	c1.print();
}
#endif

#ifdef Q7
void main()
{
	C c1(C(B(30)));
	c1.print();//error...?
}
#endif
