#include <iostream> 
using namespace std;

template<class T>
class A
{
	T* m_pt;
public:
	explicit A(T* pt)
	{
		m_pt = pt;
	}
	const A& operator=(const T& val)
	{
		*m_pt = val;
		return *this;
	}
};//class A

//#define Q_4
#define Q_5

#ifdef Q_4
void main()
{
	int i = 5;
	A<int> a(&i);
	a = 7;
	cout << i << endl;
}//main
#endif

#ifdef Q_5
void main()
{
	int i = 7, j = 8;
	A<int> a1(&i);
	A<int> a2(&j);
	a2 = a1;
	a2 = 5;
	cout << i << endl;
	cout << j << endl;
}//main
#endif





