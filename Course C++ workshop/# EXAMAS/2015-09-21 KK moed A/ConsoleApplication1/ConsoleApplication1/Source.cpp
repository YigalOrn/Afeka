#include <iostream>
using namespace std;

template <class T>
class A 
{
	T* arr;
	int size;

public:
	A(int size = 5);
	A(const T& val, int size);
	A(const A& other);

	const A& operator=(const A& other);
	virtual ~A();
	const T& operator[](int i) const;
	T& operator[](int i);

	int getSize() const;
	friend ostream& operator<<(ostream& os, const A& a) 
	{
		for (int i = 0; i < a.size; i++)
			os << a[i] << " ";
		
		return os;
	}
};//class A

template <class T>
A<T>::A(int size = 5) : size(size) 
{
	arr = new T[size];
	cout << "A::A size=" << size << endl;
}

template <class T>
A<T>::A(const T& val, int size) : size(size)
{
	arr = new T[size];
	for (int i = 0; i < size; i++)
		arr[i] = val + i;
}

template <class T>
A<T>::A(const A& other) : arr(NULL) 
{
	*this = other;
	cout << "A::A(copy) size="<<size<< endl;
}

template <class T>
A<T>::~A() 
{
	cout << "A::~A size="<<size<< endl;
	delete[]arr;
}

template <class T>
const A<T>& A<T>::operator=(const A& other) 
{
	if (this != &other) 
	{
		delete[]arr;

		size = other.size;
		arr = new T[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = other.arr[i];
		}
	}
	return *this;
}

template <class T>
const T& A<T>::operator[](int i) const
{
	return arr[i];
}

template <class T>
T& A<T>::operator[](int i) 
{
	return arr[i];
}

template <class T>
int A<T>::getSize() const 
{
	return size;
}


class Num 
{
	int i;
	static int x;

public:
	Num() : i(x) 
	{
		x++;
		cout << "Num::Num i=" << i << endl;
	}

	Num(int i) : i(i) 
	{
		cout << "Num::Num i=" << i << endl;
	}

	Num(const Num& other) : i(other.i)
	{
		cout << "Num::Num(copy) i=" << i << endl;
	}

	~Num() 
	{
		cout << "Num::~Num i=" << i << endl;
	}

	const Num& operator=(const Num& other)
	{
		if (this != &other) 
		{
			i = other.i;
		}
		return *this;
	}

	operator int() const 
	{
		return i;
	}

	void operator()(int i) 
	{
		this->i = i;
	}

	const Num& operator++() 
	{
		i++;
		return *this;
	}

};//class Num

int Num::x = 10;



int main() 
{
	void q1();
	void q2();
	void q3();
	void q4();
	void q56();

	q1();
	system("pause");
	q2();
	system("pause");
	q3();
	system("pause");
	q4();
	system("pause");
	q56();

	return 1;
}//main

void q1() 
{
	A<int> a1(2);
	A<int> a2(a1);

	cout << a1 << endl;
	cout << a2 << endl;
}

void q2()
{
	A<Num> a1(2);
	A<Num> a2(a1);

	cout << a1 << endl;
	cout << a2 << endl;
}

void q3()
{
	A<Num> a1(Num(5), 3);
	cout << a1 << endl;
}

void q4()
{
	Num arr[3];
	for (int i = 0; i < 3; i++)
		cout << ++arr[i] << " ";
	cout << endl;
}

void q56()
{
	Num arr[3];
	cout << "\n1----\n\n";
	A<int> a(3, 3);

	for (int i = 0; i < 3; i++)
		arr[i](a[i]);
	cout << "\n2----\n\n";

	for (int i = 0; i < 3; i++)
		cout << arr[i] << " ";

	cout << endl;
}

