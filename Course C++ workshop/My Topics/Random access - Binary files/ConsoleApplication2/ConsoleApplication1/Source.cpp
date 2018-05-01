#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


int main(void)
{

	//prototypes
	void writeToFile(iostream& os);
	void readFromFile(iostream& is);

	fstream fst;
	fst.open("binaryFile.cplusplus", ios::binary | ios::out | ios::trunc);
	writeToFile(fst);
	fst.close();



	//fstream fst;
	fst.open("binaryFile.cplusplus", ios::binary | ios::in);
	readFromFile(fst);
	fst.close();



	cout << "# MAIN DONE #" << endl;
	return 0;
}//main

void writeToFile(iostream& os)
{
	int size = 1108;
	int n1 = 1, n2 = 2, n3 = 3;
	double d1 = 10.1, d2 = 10.2, d3 = 10.3;
	char s1[] = "s1", s2[] = "s2s2", s3[] = "s3s3s3";
	int len1 = strlen(s1), len2 = strlen(s2), len3 = strlen(s3);



	//check file is opened...


	os.write((const char*)&size, sizeof(size));

	//------
	os.write((const char*)&n1, sizeof(n1));
	os.write((const char*)&d1, sizeof(d1));
	os.write((const char*)&len1, sizeof(len1));
	os.write((const char*)s1, (sizeof(char)*len1));
	//------

	//------
	os.write((const char*)&n2, sizeof(n2));
	os.write((const char*)&d2, sizeof(d2));
	os.write((const char*)&len2, sizeof(len2));
	os.write((const char*)s2, (sizeof(char)*len2));
	//------

	//------
	os.write((const char*)&n3, sizeof(n3));
	os.write((const char*)&d3, sizeof(d3));
	os.write((const char*)&len3, sizeof(len3));
	os.write((const char*)s3, (sizeof(char)*len3));
	//------


	
}

void readFromFile(iostream& is)
{

	int size;
	int n1, n2, n3;
	double d1, d2, d3;
	char *s1, *s2, *s3;
	int len1, len2, len3;



	//check file is opened...


	is.read((char*)&size, sizeof(size));

	//------
	is.read((char*)&n1, sizeof(n1));
	is.read((char*)&d1, sizeof(d1));
	is.read((char*)&len1, sizeof(len1));

	s1 = new char[len1 + 1];

	is.read((char*)s1, (sizeof(char)*len1));

	s1[len1] = '\0';

	//------

	//------
	is.read((char*)&n2, sizeof(n2));
	is.read((char*)&d2, sizeof(d2));
	is.read((char*)&len2, sizeof(len2));

	s2 = new char[len2 + 1];

	is.read((char*)s2, (sizeof(char)*len2));

	s2[len1] = '\0';
	//------

	//------
	is.read((char*)&n3, sizeof(n3));
	is.read((char*)&d3, sizeof(d3));
	is.read((char*)&len3, sizeof(len3));

	s3 = new char[len3 + 1];

	is.read((char*)s3, (sizeof(char)*len3));

	s3[len3] = '\0';
	//------




	cout << "n\t" << "s\t" << "d" << endl;

	cout << n1 << "\t" << s1 << "\t" << d1 << endl;

	cout << n2 << "\t" << s2 << "\t" << d2 << endl;

	cout << n3 << "\t" << s3 << "\t" << d3 << endl;



}


