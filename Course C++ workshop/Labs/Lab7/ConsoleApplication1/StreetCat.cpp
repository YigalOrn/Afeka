#include <iostream>
using namespace std;



#include "StreetCat.h"


StreetCat::StreetCat(const char* name, const char* mColor, float mLen, int numOfStreetFights) : Cat(name, mColor, mLen)
{
	this->setNumOfStreetFights(numOfStreetFights);
}

StreetCat::StreetCat(const Cat& baseClass, int numOfStreetFights) : Cat(baseClass)
{
	this->setNumOfStreetFights(numOfStreetFights);
}

StreetCat::StreetCat(const StreetCat& other) : Cat(other)
{
	*this = other;
}

void StreetCat::setNumOfStreetFights(const int numOfFights)
{
	this->numOfStreetFights = numOfFights;
}

int StreetCat::getNumOfStreetFights() const
{
	return numOfStreetFights;
}

StreetCat& StreetCat::operator=(const StreetCat& other)
{

	/*
	We should choose if to implement this or the copy-c'tor.
	There will be a collision when copying the base !!
	See copy-c'tor init-line!
	//Cat::operator=(other);
	*/

	if (this != &other)
	{
		this->setNumOfStreetFights(other.numOfStreetFights);
	}
	return *this;
	}

ostream& operator<<(ostream& os, const StreetCat& other)
{
	//Notice the casting!
	os << (Cat&)other << "StreetCat :: " << other.getNumOfStreetFights() << endl;
	return os;
}