#include <iostream>
using namespace std;

#include "Map.h"



int main(void)
{

	try
	{

		Map<int, char*> int2string;

		/*
		Notice: in the case the key isnt in the Map, we should put it there, take the garbage value of
		it and assign it the right value!

		this is all inferred from the given main !
		*/
		int2string[111] = "gogo";
		int2string[222] = "momo";
		int2string[333] = "yoyo";

		cout << int2string << endl;

		int2string[222] = "mama";

		cout << int2string << endl;


		cout << "---------------------\n\n";


		Map<char*, double> employeeToSalary;

		employeeToSalary["gogo"] = 1000;
		employeeToSalary["momo"] = 2000;
		employeeToSalary["yoyo"] = 3000;

		cout << employeeToSalary << "\n\n" << endl;

	}
	catch (char* msg)
	{
		cout << msg << endl;
	}
	catch (...)
	{
		cout << "you are not a c++ programmer" << endl;
	}

	return 1;

}//main

