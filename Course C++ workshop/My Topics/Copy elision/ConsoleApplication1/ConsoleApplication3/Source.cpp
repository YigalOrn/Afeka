#include <iostream>
using namespace std;

class A
{
public:
	A()
	{
		cout << "A::def c'tor" << endl;
	}
	A(const A& otherA)
	{
		cout << "A::copy c'tor" << endl;
	}
};


int main(void) {

	//A a1, a2, a3;

	A arr[] = { A{}, A{}, A{} };


	return 0;
}//main