#include <iostream>
using namespace std;

#include <cstdio>

#include "Set.h"



//-----------------------------------------------

int Set::serial = 1;

//constant class attributes should be initialize before the c'tor, inline !
Set::Set(int  maxSize) :maxSize(maxSize)
{
	this->currSize = 0;
	array = new int[this->maxSize];

	id = serial++;
}

//nullify the array that is a pointer so we could free the memory in operator = method
Set::Set(const Set &other) : array(0)
{
	*this = other;
}

Set::~Set()
{
	delete[]array;
}

//-----------------------------------------------

void Set::showSet() const
{

	cout << "Set " << " : maxSize = " << maxSize << " currSize = " << currSize << endl;

	for (int i = 0; i < this->currSize; i++)
	{
		printf("%6d", this->array[i]);
		if ((i + 1) % 6 == 0)
			printf("\n");
	}//for

	printf("\n");
}

bool Set::add(const int newVal)
{

	if (!checkIfInSet(newVal) && currSize < maxSize)
	{
		array[currSize++] = newVal;
		return true;
	}

	return false;
}

bool Set::checkIfInSet(const int& newVal) const
{

	for (int i = 0; i < this->currSize; i++)
	{
		if (array[i] == newVal)
			return true;
	}//for

	return false;
}

//-----------------------------------------------

/*Overloading Operators*/


const Set& Set::operator=(const Set& other)
{
	//check if different, if not there is no need to copy anything!
	if (this != &other)
	{
		maxSize = other.maxSize;
		currSize = other.currSize;

		delete[]array;

		array = new int[maxSize];

		for (int k = 0; k < currSize; k++)
		{
			/*
			The other is already a Set!
			*/
			array[k] = other.array[k];
		}

	}
	return *this;
}

Set operator+(const int& param, const Set& set)
{
	return (set + param);
}

Set operator+(const Set& set, const int& param)
{
	Set temp(set);

	//choosing to use a method instead of overloaded '+'  not friend method that copies the Set obj...
	if (!temp.add(param))
	{
		/*throw exception*/
		//cout << "#Eception adding the new value to this Set#" << endl;
	}
	return temp;
}


Set Set::operator+(const Set& other) const
{
	//it is reasonable that a union of two sets will get the max size of both of them!

	Set des(other.maxSize + (this->maxSize));

	int *s1 = this->array;
	int *s2 = other.array;

	for (; s1 < ((this->array) + (this->currSize)); s1++)
	{
		des.add(*s1);
	}

	for (; s2 < ((other.array) + (other.currSize)); s2++)
	{
		if (!des.add(*s2))
		{
			//throw exception
			//cout << "#Eception adding the new value to this Set#" << endl;
		}
	}

	return des;
}



Set Set::operator+=(int param)
{
	*this = *this + param;
	return *this;
}


ostream& operator<<(ostream& os, const Set& set)
{
	set.showSet();
	return os;
}


bool Set::operator>(const Set& other) const
{
	return (   (this->currSize>other.currSize) ? true:false   );
}


int& Set::operator[](const int index) const
{
	return this->array[index];
}


