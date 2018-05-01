#include<iostream>
using namespace std;

#include "Survivor.h"


/*C'tor*/
Survivor::Survivor(const char const * name, const float &age, const float &initialWeight, const status &st, const Bandana &bandana) : bandana(bandana)
{

	setName(name);
	setAge(age);
	setInitialWeight(initialWeight);
	setFinalWieght();//defualt -1
	setStatus(st);
}

/*D'tor*/
Survivor::~Survivor()
{
	delete[]this->name;
	cout << "\nIn Survivor::D'tor\n" << endl;
}

/*Copy C'tor - for practice*/
Survivor::Survivor(const Survivor& other)
{
	cout << "\nIn Survivor::Copy C'tor\n" << endl;
}


void Survivor::showSurvivor() const
{

	cout
		<< "Survivor : \n" << "Name - " << getName()
		<< "\nAge - " << getAge()
		<< "\nStatus - " << getStatus()
		<< "\nInitial weight - " << getInitialWeight()
		<< "\nFinal wieght - " << getFinalWieght() << endl;
}



void Survivor::setName(const char const* name)
{
	delete[]this->name;
	this->name = new char[strlen(name) + 1];
	memcpy(this->name, name, strlen(name) + 1);
}

void Survivor::setAge(const float &age)
{
	this->age = age;
}

void Survivor::setInitialWeight(const float &initialWeight)
{
}


void Survivor::setFinalWieght(const float &finalWeight)
{
	this->finalWeight = finalWeight;
}

void Survivor::setStatus(const status &st)
{
	this->st = st;
}






const char const *  Survivor::getName() const
{
	return this->name;
}

const float& Survivor::getAge() const
{
	return this->age;
}

const Survivor::status Survivor::getStatus() const
{

	return this->st;
}


const float& Survivor::getInitialWeight() const
{
	return this->initialWeight;
}

const float& Survivor::getFinalWieght() const
{
	return this->finalWeight;
}