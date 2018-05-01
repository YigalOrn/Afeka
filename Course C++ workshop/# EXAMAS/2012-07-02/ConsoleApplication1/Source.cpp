#pragma warning (disable : 4996)//for strcpy

#include <iostream>
using namespace std;



class MyString
{

	//inner class
	class MyChar
	{
		MyString* pStr;
		int index;

	public:

		MyChar(MyString* p, int i) : pStr(p), index(i) {}
		const MyChar& operator=(char c)
		{
			pStr->set(index, c); // call copy-on-write
			return *this;
		}

		operator char()const
		{
			return pStr->str[index];
		}

	};//inner class MyChar


	//private fields and methods of outer class MyString

	friend class MyChar;
	char* str;
	int* ref_counter;


	void attach(const MyString& s)
	{
		str = s.str;
		ref_counter = s.ref_counter;
		++(*ref_counter);

	}

	void detach()
	{
		if (--(*ref_counter) == 0)
		{
			delete[]str;
			delete ref_counter;
		}
	}

	void set(int index, char c)
	{
		// this is the copy-on-write
		MyString temp(str);
		detach();
		attach(temp);
		str[index] = c;
	}


public:

	//def c'tor
	MyString(char* s = "") : ref_counter(new int(1))
	{
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}

	//copy c'tor
	MyString(const MyString& s)
	{
		attach(s);
	}

	~MyString()
	{
		detach();
	}

	const MyString& operator=(const MyString& s)
	{
		detach(); attach(s); return *this;
	}

	operator const char*()const
	{
		return str;
	}

	MyChar operator[](int index)
	{
		return MyChar(this, index);
	}

	char operator[](int index) const
	{
		return str[index];
	}

	friend ostream& operator<<(ostream& out, const MyString& s)
	{
		return out << s.str << ", ref count = " << *s.ref_counter << endl;
	}

};


int main()
{
	MyString s1;
	cout << s1;

	MyString s2 = s1, s3 = s1; //using explicit copy c'tor the syntax should be s2(s1)
	cout << s3;

	s1 = "Hello";
	cout << s3;

	s3 = s2 = s1;
	cout << s3;

	//non-const object will always prefer calling a non-const method over a const method!
	cout << "s1[0] = " << s1[0] << endl;
	s2[4] = '!';
	cout << s3 << s2;

	return 1;
}//main










