#include <iostream> 
using namespace std;

class A 
{
	static A* pLastAborn;
	A *prev, *next;
public:
	A() :prev(pLastAborn), next(NULL) 
	{
		if (pLastAborn)
			pLastAborn->next = this;
		pLastAborn = this;
	}
	virtual void Print() const
	{
		if (next)
			next->Print();
	}
	virtual ~A() 
	{
		if (this->prev)
			this->prev->next = this->next;
		if (this->next)
			this->next->prev = this->prev;
		else
			pLastAborn = this->prev;
	}
};//class A

class B : public A 
{
	char c;
public:
	B(char c1) :c(c1) {}
	void Print() const 
	{
		cout << c << endl;
		A::Print();
	}
	~B() { Print(); }
};//class B

A* A::pLastAborn;




//#define Q_1_2
#define Q_3



#ifdef Q_1_2
void main() 
{
	B x1('a'), x2('b'), x3('c');
	x1.Print();
}//main
#endif

#ifdef Q_3

void main() 
{
	A* pa = new B('a');
	B b2('b'), b3('c');
	pa->Print();
	delete pa;
}//main

#endif

