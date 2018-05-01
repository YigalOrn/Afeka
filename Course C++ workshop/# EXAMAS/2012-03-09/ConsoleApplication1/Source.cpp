/*
https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern

https://katyscode.wordpress.com/2013/08/22/c-polymorphic-cloning-and-the-crtp-curiously-recurring-template-pattern/
*/

#include <iostream>
using namespace std;

template<class T>class Counter
{
	static int counter;
	const int id;
public:
	Counter() :id(++counter) {}
	int getId() { return id; }
	static int getCounter() { return counter; }
};

class B : public Counter<B> {};
class C : public Counter<C> {};

// in Counter.cpp:
template<class T>
int Counter<T>::counter = 0;

//----------------
// main.cpp
//----------------
int main()
{
	B b;
	cout << B::getCounter() << endl << b.getId() << endl;
	cout << C::getCounter() << endl;

	C* pc = new C();
	cout << B::getCounter() << endl;
	cout << C::getCounter() << endl << pc->getId() << endl;

	return 1;
}
