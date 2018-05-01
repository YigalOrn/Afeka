#include <iostream>
#include <fstream>
using namespace std;


int main(void)
{

	fstream fromFile, toFile;

	fromFile.open("xampp-win32-5.6.12-0-VC11-installer.exe", ios::in | ios::binary);

	toFile.open("Copy.exe", ios::out | ios::binary | ios::trunc);


	char byte;

	while (fromFile && !fromFile.eof())
	{
		//read a byte from src
		fromFile.read((char*)&byte, sizeof(char));

		//write byte to des/new file
		toFile.write((const char*)&byte, sizeof(char));

	}//while

	fromFile.close();
	toFile.close();

	cout << "# MAIN DONE #" << endl;
	return 0;
}//main













