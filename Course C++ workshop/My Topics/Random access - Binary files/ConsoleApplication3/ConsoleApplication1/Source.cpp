#include <iostream>
#include <fstream>
using namespace std;

class ObjectA
{

public:

	ObjectA(int num1 = 1, int num2 = 2, double dNum = 100.001, bool bVal = false)
	{
		n1 = (num1 += increment);
		n2 = (num2 += increment);
		d1 = (dNum += increment);

		if (n1 % 2 == 0)
		{
			boolVal = true;
		}
		increment++;
	}


	void show(ostream& os)
	{
		if (typeid(os) == typeid(ostream))
		{
			os << "ObjectA data members are:\n" << "n1 - " << n1 << ", n2 - " << n2 << ", d1 - " << d1 << ", boolVal  - ";

			if (boolVal == true) 
			{
				cout << "true" << endl;
			}
			else
			{
				cout << "false" << endl;
			}

		}
	}

private:

	static int increment;

	int n1;
	int n2;
	double d1;
	bool boolVal;

};
int ObjectA::increment = 1;



int main(void)
{

	//prototypes
	void writeToFile(iostream& os);
	void readFromFile(iostream& is);

	fstream fst;
	fst.open("binaryFile.cplusplus", ios::binary | ios::out | ios::trunc);
	writeToFile(fst);//write
	fst.close();


	fst.open("binaryFile.cplusplus", ios::binary | ios::in);
	readFromFile(fst);//read
	fst.close();



	cout << "# MAIN DONE #" << endl;
	return 0;
}//main

void writeToFile(iostream& os)
{

	cout << "How many objects to test : " << endl;
	int size;
	cin >> size;

	ObjectA *arr = new ObjectA[size];//creation with def c'tor

	//write the arr size
	os.write((const char*)&size, sizeof size);

	//------------------
	for (int i = 0; i < size; i++)
	{
		os.write((const char*)&arr[i], sizeof(ObjectA));
	}//for
	//------------------



	//free mem
	delete[]arr;

}

void readFromFile(iostream& is)
{
	int size;

	//write the arr size
	is.read((char*)&size, sizeof size);

	ObjectA *arr = new ObjectA[size];//creation with def c'tor



	//------------------
	for (int i = 0; i < size; i++)
	{
		is.write((char*)&arr[i], sizeof(ObjectA));
	}//for
	 //------------------


	cout << "#########################################" << endl;
	for (int i = 0; i < size; i++)
	{
		arr[i].show(cout);
	}
	cout << "#########################################" << endl;

	//free mem
	delete[]arr;
}


