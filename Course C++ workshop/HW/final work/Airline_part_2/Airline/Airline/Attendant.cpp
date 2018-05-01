#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
using namespace std;

#include "Attendant.h"



Attendant::Attendant(const Person& p, int seniority, double salary)  
throw (const char*)  
	: Person(p), AirCrew(p, seniority, salary), amountOfLanguages(0)

{
	addLanguage("English");
}

Attendant::Attendant(const Attendant& other) 
throw (const char*)
	: Person(other.getName(), other.getAge()), AirCrew(other), amountOfLanguages(0)

{
	for (int i = 0; i < other.getAmountOfLanguages(); i++)
	{
		addLanguage(other.getLanguages()[i]);
	}
}

Attendant::~Attendant()
{
	for (int i = 0; i < amountOfLanguages; i++)
	{
		delete []languages[i];
	}
}

AirCrew* Attendant::clone() const // for Prototype design pattern
{
	return new Attendant(*this);
}

void Attendant::addLanguage(const char* language) throw (const char*)
{
	if (!language)
	{
		throw "# Language can't be empty #";
	}

	if (amountOfLanguages == MAX_NUMBER_OF_LANGUAGES) 
	{
		throw "# Languages amount exceeded the max capacity #";
	}

	languages[amountOfLanguages] = new char[strlen(language) + 1];
	strcpy(languages[amountOfLanguages], language);
	amountOfLanguages++;
}

 void Attendant::toOs(ostream& out) const 
{
	out << "Languages spoken: " << getAmountOfLanguages() << endl;
	for (int i = 0; i < getAmountOfLanguages(); i++)
	{
		out << getLanguages()[i] << "  " << endl;
	}
}

const char*const* Attendant::getLanguages() const
{
	return languages;
}