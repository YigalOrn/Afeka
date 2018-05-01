/*
https://msdn.microsoft.com/en-us/library/dd293608.aspx

http://stackoverflow.com/questions/11323811/c-what-is-meant-by-retain-state

*/


#include <iostream>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;


void abssort(float* x, unsigned n) {

	int num1 = 9;
	int num2 = 99;
	double d1 = 1.233;

	sort(x, x + n,

		// Lambda expression begins
		[&num1, &num2, &d1](float a, float b)
	{
		//cout << num1 << num2 << d1 << endl;
		return (abs(a) < abs(b));

	} // end of lambda expression

	);
}

bool greaterThen9(int x1)
{
	return x1 > 9;
}

void q1(void)
{
	const int SIZE = 10;
	int arr[] = { 99, 1, -9, 5, 6, 4, 3, 1, 14, 0 };
	vector<int> vec(arr, arr + SIZE);

	ostream_iterator<int> output(cout, " ");
	copy(vec.begin(), vec.end(), output);


	vector<int>::iterator newLastElement =
		remove_if(vec.begin(), vec.end(), [](int x1) {return x1 > 9;});
	cout << endl;
	copy(vec.begin(), newLastElement, output);



}//q1

void q2(void)
{
	int n = 0;
	auto x = [=]() mutable { return n++; };
	cout << x() << '\n';
	cout << x() << '\n';
	cout << x() << '\n';
	cout << endl;
	cout << "n = " << n << '\n';

}//q2


int main(void)
{

	q1();
	//q2();

	cout << endl;
	return 0;
}//main








