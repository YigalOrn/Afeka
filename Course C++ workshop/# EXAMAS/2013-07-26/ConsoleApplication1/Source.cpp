#include <iostream>
#include <typeinfo>
using namespace std;



template<class T>
class Base
{
protected:
	T *data;
	int *num;
public:
	Base(const T& val)
		: data(new T(val)), num(new int(1)) {}
	Base(const Base<T>& par)
		: data(par.data), num(par.num)
	{
		(*num)++;
	}
	const Base<T>& operator=(const Base<T>& par)
	{
		data = par.data;
		num = par.num;
		(*num)++;
		return *this;
	}
	void print()const
	{
		cout << *data << endl << *num << endl;
	}
	virtual ~Base()
	{
		(*num)--;
		if (*num == 0)
		{
			delete data;
			delete num;
		}
	}
};//Base

template<class T>
class Inherit :public Base<T>
{
public:
	Inherit(const T& val) :Base<T>(val)
	{
		*num = 2;
	}
	Inherit(const Inherit<T>& b) :Base<T>(b)
	{
		(*num)++;
	}
	~Inherit()
	{
		(*num)--;
	}
};//Inherit




//#define Q1
//#define Q2
//#define Q3
//#define Q5_6
#define Q7



#ifdef Q1
void main()
{
	Inherit<double> b(24.6);
	Base<double> a(b);
	a.print();
}
#endif


#ifdef Q2
void main()
{
	Inherit<double> b(24.6);
	Inherit<double> a(b);
	a.print();
}
#endif


#ifdef Q3
void main()
{
	Inherit<double> b(24.6);
	Inherit< Inherit<double> > a(b);
	//a.print();
}
#endif


#ifdef Q5_6
void main()
{
	Base<int*> ptr(new int(7));
	ptr.print();
}
#endif


#ifdef Q7
void main()
{
	Base<int> *p;
	p = new Inherit<int>(8);
	cout << typeid(*p).name();
}
#endif



