#include <iostream>
using namespace std;

class F
{
	float f;
public:
	F(float g) :f(g)
	{}
};

template <class T>
void func(T a)
{
	cout << a;
}

void main()
{
	F o(2.3);

	func(2.3);
	func(o);
}
