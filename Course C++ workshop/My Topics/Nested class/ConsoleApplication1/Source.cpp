/*
https://msdn.microsoft.com/en-us/library/71dw8xzh.aspx
*/



#include <iostream>
using namespace std;


class Enclose1
{

	int enclose1_x;
	const double enclose1_d{ 9 };
	static bool enclose1_val;

	void e1_1(void) {/*....*/ }
	static void e1_2(void) {/*....*/ }
	static void e1_3(void);


public:
	class Inner1
	{
		int inner1_x;
		static bool inner1_val;

	public:
		void foo1(void);//declaration
		void foo2(int num) {/*....*/ }//definition-implementation
		void foo3(void)
		{//member method

			cout << inner1_x << endl;
			cout << enclose1_x << endl;
			cout << enclose1_d << endl;
			cout << enclose1_val << endl;

			e1_1();
			e1_2();
			Enclose1::e1_2();
			e1_3();


			cout << sizeof(enclose1_x) << endl;

		}
		static int foo4(void) { return 0; }
	};//Inner1


	void e1_4(void)
	{
		cout << inner1_x << endl;
		cout << Inner1::inner1_x << endl;
		cout << Inner1::foo1() << endl;
		cout << Inner1::foo4() << endl;
		cout << foo4() << endl;
	}

	static void e1_5(void) {/*....*/ }

};//Enclose1

bool Enclose1::enclose1_val = false;

void Enclose1::Inner1::foo1(void) {/*....*/ }//implement
bool Enclose1::Inner1::inner1_val = false;


class Enclose2
{
	//in private specifier
	class Inner2
	{

	};//Inner2

};//Enclose2

template<class T>
class Enclose3<T>
{

	class Inner3
	{
		T temp;
	};//Inner3

};//Enclose3

class Enclose4
{

	class Inner4
	{
	public:
		void foo(Enclose4& refObj)
		{
			refObj.x;
		}

	};//Inner4

	friend Inner4;
	int x;


};//Enclose4



class Enclose5
{

public:

	template<typename T>
	class Inner5
	{
		T data;
		T* dataPtr;

	public:
		
		void gooGoo1(T t);

	};//Inner5
	
	
};//Enclose5

template<typename T>
void Enclose5::Inner5<T> gooGoo1(T t) {/*...*/}






template<class Q>
class Enclose6
{

public:

	template<typename T>
	class Inner6
	{
		T data;
		T* dataPtr;

	public:

		void foofoo1(T t);

	};//Inner6


};//Enclose6

template<class Q>
template<typename T>
void Enclose6<Q>::Inner6<T> gooGoo1(T t) {/*...*/ }





void main(void)
{

	Enclose1::Inner1 inner1;
	Enclose2::Inner2 inner2;

	Enclose1::Inner1::foo4();
	Enclose1::e1_5();

}//main







