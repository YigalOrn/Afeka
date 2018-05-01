#include<iostream>
#include <typeinfo>
using namespace std;

template<class T>
class Base
{
protected:
	T val;
public:
	Base(const T& t) : val(t)
	{
		cout << "In Base::Base, val is of type"
			<< typeid(t).name() << endl;
	}

	virtual ~Base() {}

	
	friend ostream& operator<<(ostream& os, const Base& b)
	{
		os << "My type is |" << typeid(b).name() << "|\n";
		os << "My T is of type |" << typeid(val).name() << "|\n";
		os << "and its value is |" << b.val << "|\n";
		return os;
	}
	

};


template<class T>
class Derived : public Base<T>
{
public:
	Derived(const T& t) :Base(t)
	{
		cout << "In Derived::Derived" << endl;
	}
};


int main(void)
{
	Derived<char> d('a');
	cout << d << endl;

	return 0;
}//main

