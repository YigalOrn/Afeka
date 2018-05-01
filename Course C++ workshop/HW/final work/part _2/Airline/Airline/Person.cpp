#include "Person.h"

Person::Person(const string& newName, int age) : age(age)
{
	setName(newName);
}

Person::Person(const Person& p) : Person(p.getName(), p.getAge())
{}

Person::~Person(){}

void Person::setName(const string& newName) throw (const string&)
{
	if (newName.empty())
	{
		throw string("# Name provided cannot be NULL #");
	}	
	name.assign(newName);
}

void Person::setAge(int age) throw (const string&)
{
	if (age <= 0)
	{
		throw string("# Age cannot be negative #");
	}	
	this->age = age;
}

const string& Person::getName() const
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

bool Person::operator==(const Person& other) const
{
	return (name == other.getName()) && (age == other.getAge());
}