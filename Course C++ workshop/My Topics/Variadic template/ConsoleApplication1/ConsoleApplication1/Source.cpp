#include<iostream>
using namespace std;

float sum()
{
	return 0;
}

template<typename...Types>
float sum(float n1, Types...rest)
{
	return (n1 + sum(rest...));
}

void main()
{

	cout << sum(1, 2, 3.3f, 4, 5.211f) << endl;

}//main
