#include <iostream>
using namespace std;

#include <cstring>

#include "SiamiCat.h"



SiamiCat::SiamiCat(const char* name, const char* mColor, float mLen, const char* foodILike) : Cat(name, mColor, mLen), foodILike(0)
{
	this->setFood(foodILike);
}

SiamiCat::SiamiCat(const Cat& baseClass, const char* foodILike) : Cat(baseClass), foodILike(0)
{
	this->setFood(foodILike);
}

SiamiCat::SiamiCat(const SiamiCat& other) : Cat(other), foodILike(NULL)
{
	*this = other;
}

SiamiCat::~SiamiCat()
{
	delete[]foodILike;
}

void SiamiCat::setFood(const char* foodILike)
{
	delete[]this->foodILike;
	this->foodILike = _strdup(foodILike);
}

const char* const SiamiCat::getFood() const
{
	return this->foodILike;
}

//Call baseClass operator=
SiamiCat& SiamiCat::operator=(const SiamiCat& other)
{
	/*
	We should choose if to implement this or the copy-c'tor.
	There will be a collision when copying the base !!
	See copy-c'tor init-line!
	//Cat::operator=(other);
	*/

	if (this != &other)
	{
		this->setFood(other.getFood());
	}

	return *this;
}

ostream& operator<<(ostream& os, const SiamiCat& other)
{
	//Notice the casting!
	os << (Cat&)other << "SiamiCat :: " << other.getFood() << endl;
	return os;
}