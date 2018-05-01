#include <iostream>
using namespace std;


template<class T>
class A
{
	T t;
public:
	A(T p) : t(p) {}
	const A<T>& operator=(const A<T>& val)
	{
		t = val.t;
		return *this;
	}
};//A


template<class T>
class Son : public A<T>
{
public:
	Son(T p) : A<T>(p) {}
};//Son




#define Q5
//#define Q6




#ifdef Q5
int main()
{
	A<int> a(1);
	Son<int> b(2);
	Son<int>& c = b;
	b = a;
}
#endif


#ifdef Q6
int main()
{
	A<int> a(2);
	A<int> b(1);

	Son<A<int>> s1(a);
	Son<A<int>> s2(b);

	s1 = s2;

	system("puase");

}
#endif
















