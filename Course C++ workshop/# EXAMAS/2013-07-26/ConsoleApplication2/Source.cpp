#include <iostream>
using namespace std;

void main()
{
	/*

	//int i = 7;
	//int *ptr = new int(7);
	int** data = new int*( new int(7) );

	int *ptr2 = *data;//copy address

	//**data = 0;
	
	delete *data;
	//delete data;


	//cout << **data << endl;//run time error
	cout << *ptr2 << endl;

	*/


	int *ptr1 = new int(777777);
	int *ptr2(ptr1);


	cout << *ptr1 << endl;
	cout << *ptr2 << endl;



	system("pause");

}//main



