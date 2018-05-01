#include <iostream>
#include <typeinfo>
using namespace std;


template<class T1, class T2>  void foo(T1, T2)      { cout << "1" << endl; }
template<class T>             void foo(T)           { cout << "2" << endl; }
template<class T>             void foo(T, T)        { cout << "3" << endl; }
//template<class T>             void foo(T*)          { cout << "4" << endl; }
template<class T>             void foo(T*, T)       { cout << "5" << endl; }
template<class T>             void foo(T, T*)       { cout << "6" << endl; }
template<class T>             void foo(int, T*)     { cout << "7" << endl; }
template<>                    void foo<int>(int)    { cout << "8" << endl; }
                              void foo(int, double) { cout << "9"<< endl; }
                              void foo(int)         { cout << "10" << endl; }



template<class T>
class complex
{};


void main()
{

	int i = 0;
	double d = 0;
	float ff = 0;
	complex<double> c;

	foo(i);
	foo<int>(i);
	foo(i, i);
	foo(c);
	foo(i, ff);
	foo(i, d);
	foo(c, &c);
	foo(i, &d); //
	foo(&d, d);
	foo(&d);
	foo(d, &i);
	foo(&i, &i); //


}//main


