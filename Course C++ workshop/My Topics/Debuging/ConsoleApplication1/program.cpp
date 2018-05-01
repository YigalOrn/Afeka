/*
https://msdn.microsoft.com/en-us/library/b0084kay.aspx
*/

#include <iostream>
using namespace std;


//#define DEBUG_MODE

void foo1()
{
	cout << __FUNCTION__ << endl;
	cout << "line:" << __LINE__ << endl;
	cout << "###################################" << endl;
}

void foo2()
{
	cout << __FUNCTION__ << endl;
	cout << "line:" << __LINE__ << endl;
	cout << "###################################" << endl;
}


int main(void)
{

	foo1();


	cout << __FUNCTION__ << endl;
	cout << "line:" << __LINE__ << endl;
	cout << __TIME__ << endl;
	cout << "###################################" << endl;



	cout << __FUNCTION__ << endl;
	cout << "line:" << __LINE__ << endl;
	cout << __DATE__ << endl;
	cout << "###################################" << endl;

	foo2();


	cout << __FILE__ << endl;
	cout << "line:" << (__LINE__ -1) << endl;
	

	
	std::cout << __func__ << std::endl
		<< __FUNCTION__ << std::endl;
		//<< __PRETTY_FUNCTION__ << std::endl;


#ifdef DEBUG_MODE

	cout << "IN DEBUG_MODE" << endl;

#endif


	cout << "# MAIN DONE #" << endl;
	return 0;
}//main















