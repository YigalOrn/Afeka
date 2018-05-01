#include <string>
#include <iostream>
using namespace std;

template<class T>
class Base 
{
private :
	T t;
protected:
	static int countBase;
public:
	Base(const T& t1) : t(t1) 
	{
		countBase++;
	}
	static int get_countBase() { return countBase; }
	~Base() 
	{
		countBase--;
	}
	friend ostream& operator<<(ostream& os, const Base<T>& b) 
	{
		return os << b.t;
	}

	template<class S>
	void assign(const S& s) 
	{
		t = *s;
	}
};

template<class T>
class Derived : public Base<T> 
{
public:
	Derived(const T &t) : Base<T>(t) 
	{}
};

template<class T>
int Base<T>::countBase;



#define Q1
#define Q2
#define Q3
#define Q4



#ifdef Q1
void main() 
{
	Base<int> A(7);
	Derived<int> B(9);
	cout << B << ' '<<Base<int>::get_countBase()<< endl;
}
#endif

#ifdef Q2
void main()
{
	Base<int> A(7);
	Derived<double> B(9.9);
	cout << B << ' ' << Base<double>::get_countBase() << endl;
}
#endif

#ifdef Q3
void main() 
{
	Base<string> A("hello");
	A.assign(new string("bye"));
	cout << A;
}
#endif

#ifdef Q4
void main() 
{
	int i = 10;
	const Base<double> A(2);
	cout << A.get_countBase();
	A.assign(&i);
}
#endif








