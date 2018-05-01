#include <iostream>
using namespace std;

#include <cstring>

#include "Cat.h"


Cat::Cat(const char* name, const char* mColor, float mLen) : name(0), mColor(0), mLen(mLen)
{
	setName(name);
	setMcolor(mColor);
}

Cat::~Cat()
{
	delete[]name;
	delete[]mColor;
}

Cat::Cat(const Cat& other) : name(0), mColor(0)
{
	*this = other;
}


Cat& Cat::operator=(const Cat& other)
{
	if (this != &other)
	{
		this->setName(other.getName());
		this->setMcolor(other.getMcolor());
		this->setLen(other.getLen());
	}

	return *this;
}

//friend
ostream& operator<<(ostream& os, const Cat& other)
{
	os << "Cat :" << other.getName() << " " << other.getMcolor() << " " << other.getLen() << endl;
	return os;
}

void Cat::setName(const char* name)
{

	delete[]this->name;
	//this->name = new char[strlen(name) + 1];
	//memcpy(this->name, name, strlen(name) + 1);
	this->name = _strdup(name);
}

const char* const Cat::getName() const
{
	return name;
}

void Cat::setMcolor(const char* mColor)
{
	delete[]this->mColor;
	//this->mColor = new char[strlen(mColor) + 1];
	//memcpy(this->mColor, mColor, strlen(mColor) + 1);
	this->mColor = _strdup(mColor);
}

const char* const Cat::getMcolor() const
{
	return mColor;
}

void Cat::setLen(const float len)
{
	this->mLen = len;
}

float Cat::getLen() const
{
	return this->mLen;
}