#include <iostream>
#include <list>
#include <string>
using namespace std;


template<class T> class MaxMinFinder
{
	T m_max, m_min;
public:
	template<class Iterator>
	MaxMinFinder(Iterator begin, Iterator end)
		: m_max(*begin), m_min(*begin)
	{
		for (; begin != end; ++begin)
			(*this)(*begin);
	}
	void operator()(const T& t)
	{
		if (t > m_max)
			m_max = t;
		else if (t < m_min)
			m_min = t;
	}
	friend ostream& operator<<
		(ostream& out, const MaxMinFinder<T>& f)
	{
		return out << "max: " << f.m_max << ", min: " << f.m_min;
	}
};


class intMaxMinFinder : public MaxMinFinder<int>
{
public:
	template<class Iterator>
	intMaxMinFinder(Iterator begin, Iterator end) :
		MaxMinFinder<int>(++begin, --end) {}
};



#define Q1
//#define Q2
//#define Q3
//#define Q6_7


#ifdef Q1
void main()
{
	int iArr[] = { 15, 5, 70, 2 };
	int iArrSize = sizeof(iArr) / sizeof(iArr[0]);
	MaxMinFinder<int> iMMF(iArr, iArr + iArrSize);
	cout << iMMF << ", ";

	list<string> sList;
	sList.insert(sList.end(), "small");
	sList.insert(sList.end(), "smallish");
	sList.insert(sList.end(), "big");
	sList.insert(sList.end(), "biggish");
	MaxMinFinder<string> sMMF(sList.begin(), sList.end());
	cout << sMMF << endl;
}
#endif

#ifdef Q2
void main()
{
	int* pInt = new int(3);
	MaxMinFinder<int> MMF(pInt, pInt + 1);
	cout << MMF << endl;
	delete pInt;
}
#endif

#ifdef Q3
void main()
{
	int arr[] = { 0,1 };
	cout << MaxMinFinder<int>(arr, arr + 1) << endl;
}
#endif

#ifdef Q6_7
void main()
{
	int arr[] = { 1,2,3 };
	cout << intMaxMinFinder(arr, arr + 3) << endl;
	// cout<<intMaxMinFinder(arr-1, arr+4)<<endl;
}
#endif


