#include <iostream>
using namespace std;

#include <memory>
using std::auto_ptr;

#include <cstring>



class G
{

	char* str;

public:

	G(const char* str)
	{
		setStr(str);
	}

	~G()
	{
		cout << "In G::d'tor" << endl;
		delete[]str;
	}

	void setStr(const char* str)
	{
		str = _strdup(str);
	}

	const char* getStr() const
	{
		return str;
	}

};

class A
{

private:

	auto_ptr<G> apStr;
	int num;

public:

	A(char* str, int num) :apStr(new G(str)), num(num)
	{

		cout << "In A::c'tor" << endl;
		throw "exception from A c'tor";
	}

};//A




int main(void)
{

	try
	{
		A a("str test", 5);
	}
	catch (...)
	{
	}


	cout << "# MAIN DONE #" << endl;
	return 0;
}//main




