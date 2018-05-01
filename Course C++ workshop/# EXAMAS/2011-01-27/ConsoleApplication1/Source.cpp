#include <iostream>
#include <string>
using namespace std;


template<class T> class Pointers
{
	T *p, *q;
	static int num;
public:
	Pointers(T* param) : p(param), q(new T(*param))
	{
		num++;
	}
	~Pointers() { num--; }
	static int get_num() { return num; }
	T& operator*() { return *p > *q ? *p : *q; }
	friend ostream& operator<<
		(ostream& out, const Pointers<T>& o) {
		return out << *o.p << endl << *o.q;

	}
	class G
	{
	public:
		~G() { cout << Pointers<T>::get_num() << endl; }
	};
};



template<class T> int Pointers<T>::num;



class StringPointers : public Pointers<string>
{
public:
	StringPointers(string* s) : Pointers<string>(s) {}
};




//#define Q1_4
//#define Q5
#define Q6_7



#ifdef Q1_4
void main()
{
	Pointers<int>::G g;

	int i = 7;
	Pointers<int> a(&i);
	Pointers<int> b = a;
	i = 10;
	cout << b << endl;
}
#endif


#ifdef Q5
void main()
{
	Pointers<int>::G g;
	int i = 1;
	Pointers<int> a(&i);
	++i;
	Pointers<int> *pb = new Pointers<int>(&i);
	cout << *a << endl << *pb << endl;
}
#endif


#ifdef Q6_7
void main()
{
	string str = "Hello";
	StringPointers a(&str);
	str = "World";
	//cout << a << endl;
	
	Pointers<StringPointers> b(&a);
	str = "NewWorld";
	cout << b << endl;
}
#endif











