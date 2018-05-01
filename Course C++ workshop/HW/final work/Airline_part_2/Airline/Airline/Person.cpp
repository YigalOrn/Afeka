#include <iostream>
#include <cstring>
using namespace std;

#include "Person.h"

Person::Person(const char* newName, int age) : name(0), age(age)
{
	setName(newName);
}

Person::Person(const Person& p) : Person(p.getName(), p.getAge())
{}

Person::~Person()
{
	delete []name;
}

void Person::setName(const char* newName) throw (const char*)
{
	if (!newName)
	{
		throw "# Name provided cannot be NULL #";
	}	
	delete[] this->name;
	this->name = new char[strlen(newName) + 1];
	if (!this->name)
	{
		throw "# No more memory available #";
	}
	strcpy(this->name, newName);
}

void Person::setAge(int age) throw (const char*)
{
	if (age <= 0)
	{
		throw "# Age cannot be negative #";
	}	
	this->age = age;
}

const char* Person::getName() const
{
	return name;
}

int Person::getAge() const
{
	return age;
}

ostream& operator<<(ostream& out, const Person& p)
{
	out << "Person name : " << p.getName() << endl;
	out << "Person age : " << p.getAge() << endl;
	return out;
}

/*
const Person& Person::operator=(const Person& other)
{
	if (this != &other)
	{
		setName(other.getName());
		setAge(other.getAge());
	}
	return *this;
}
*/

bool Person::operator==(const Person& other) const
{
	return (strcmp(name, other.getName()) == 0) && (age == other.getAge());
}