#include <iostream>
using namespace std;

class Frac
{
protected:
	int a, b;
public:
	Frac(int x, int y) :a(x), b(y)
	{}

	virtual operator float()
	{
		return (float)a / b;
	}

	friend void Print(Frac var)
	{
		cout << var << endl;
	}
};


class TwiceFrac : public Frac
{
public:
	TwiceFrac() :Frac(1, 2)
	{}
	virtual operator float()
	{
		return (float)a / b * 2;
	}
};



//#define Q4
//#define Q5
//#define Q6
#define Q7

#ifdef Q4
void main()
{
	TwiceFrac obj;
	Print(obj);
}
#endif

#ifdef Q5
void main()
{
	TwiceFrac obj;
	cout << obj << endl;
}
#endif

#ifdef Q6
void main()
{
	Frac *p = new TwiceFrac;
	Print(*p);
}
#endif

#ifdef Q7
//change inheritance to protected
void main()
{
	Frac *p = new TwiceFrac;
	cout << *p << endl;
}
#endif