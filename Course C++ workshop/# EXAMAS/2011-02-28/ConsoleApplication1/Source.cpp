#include <iostream>
#include <string>
using namespace std;

template<class T>
class A
{
public:
	static T* max;
	A(T* t)
	{
		if (max == NULL || *t > *max) {
			delete max; //deletion of NULL is OK
			max = t;
		}
		else {
			delete t;
		}
	}
	T& operator*() { return max; }
	operator T*() { return max; }
};//A

template<class T> T* A<T>::max;


class StringA :public A<string>
{
public:
	StringA(string* s) : A<string>(s) {}
};//StringA



//#define Q5
//#define Q6
#define Q7



#ifdef Q5
int main()
{
	A<int> a1 = new int(5);
	A<int> a2 = new int(4);
	cout << *(A<int>::max) << endl;
	return 0;
}//main
#endif

#ifdef Q6
int main()
{
	string str = "Hello";
	StringA a(&str);
	cout << *(a.max) << endl;
	return 0;
}//main
#endif

#ifdef Q7
int main()
{
	StringA s1 = new string("Hello");
	A<string> s2 = s2;
	StringA s3 = new string("World");
	cout << *(s1.max) << endl;
	return 0;
}//main
#endif



