#include <iostream>
#include <fstream>
using namespace std;


int main(void)
{

	char* fileName = "D:\\Programs\\win 7 home premium 64 bit original bootable copy.zip";
	fstream fromFile, toFile;

	fromFile.open(fileName, ios::in | ios::binary);

	if (!fromFile)
	{
		cout << "Error creating fromFile" << endl;
		exit(1);
	}

	toFile.open("Copy.zip", ios::out | ios::binary | ios::trunc);

	if (!toFile)
	{
		cout << "Error creating toFile" << endl;
		exit(1);
	}
	
	char bytes[1000];

	while (fromFile && !fromFile.eof())
	{
		//read a byte from src
		fromFile.read((char*)bytes, sizeof(bytes));

		//write byte to des/new file
		toFile.write((const char*)bytes, sizeof(bytes));

	}//while

	fromFile.close();
	toFile.close();

	cout << "# MAIN DONE #" << endl;
	return 0;
}//main













