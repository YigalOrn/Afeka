template<class T>
class A
{
protected:
	T *data;
	int *num;
public:
	A(const T &p) : data(new T(p)), num(new int(1)) {}
	A(const A<T> &b) : data(b.data), num(b.num)
	{
		(*num)++;
	}
	const A<T>& operator=(const A<T>& b)
	{
		data = b.data;
		num = b.num;
		(*num)++;
		return *this;
	}
	virtual void print() const
	{
		cout << *data << endl << *num << endl;
	}
	virtual ~A()
	{
		(*num)--;
		if (*num == 0)
		{
			delete data;
			delete num;
		}
	}
};


template <class T>
class Son : public A<T>
{
public:
	Son(const T &p) :A<T>(p)
	{
		*num = 2;
	}
	Son(const Son<T> &b) : A<T>(b)
	{
		(*num)++;
	}
	~Son()
	{
		(*num)--;
	}
};



#define Q1
//#define Q2
//#define Q3
//#define Q4
//#define Q5



#ifdef Q1
int main()
{
	A<int> a(23);
	A<int> b(a);
	b.print();
	return 0;
}
#endif

#ifdef Q2
int main()
{
	A<int> a(23);
	A<int> b(a);
	a.print();
	return 0;
}
#endif

#ifdef Q3
int main()
{
	A<int> a(23);
	A<int> b(a);
	a = b;
	a.print();
	return 0;
}
#endif

#ifdef Q4
int main()
{
	Son<int> b(23);
	A<int> a(b);
	a.print();
	return 0;
}
#endif

#ifdef Q5
int main()
{
	Son<int> s1(50);
	Son<int> s2(s1);
	s2.print();
	return 0;
}
#endif



