#include <iostream>
using namespace std;

class TObject
{

public:
	TObject(int aType = 0) :m_type(aType), m_id(++s_idCounter) { cout << m_id; }
	virtual ~TObject() { print(); }
	int getId()const { return m_id; }
	int getType()const { return m_type; }
	virtual void print()const { cout << m_id; }
private:
	static int s_idCounter;
	int m_type;
	int m_id;
};//TObject

int TObject::s_idCounter;

template<class T>
class Array : public TObject
{
public:
	Array(unsigned arraySize = 8) :m_data(0), m_size(arraySize) { m_data = new T[arraySize]; }
	~Array() { delete[]m_data; }
	T& operator[](unsigned index)
	{
		if (index >= m_size)
		{
			index = 0;
		}
		return m_data[index];
	}
	virtual void print() const
	{
		while (m_size--)
		{
			cout << getId();
		}
	}
protected:
	T* m_data;
	mutable unsigned  m_size;
};//Array



//#define Q1
//#define Q2
//#define Q3
#define Q4


#ifdef Q1
void main()
{
	Array<int> b(4);
}
#endif


#ifdef Q2
void main()
{
	Array<TObject> b(4);
}
#endif


#ifdef Q3
void main()
{
	Array<Array<int>> b(4);
}
#endif


#ifdef Q4
void main()
{
	Array<double> b(4);
	b[0] = 3.5;
	b.print(); //use debugger
}
#endif



