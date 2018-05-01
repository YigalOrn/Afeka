#include "Attendant.h"

Attendant::Attendant(const Person& p, int seniority, double salary)  
throw (const string&)  
	: Person(p), AirCrew(p, seniority, salary), amountOfLanguages(0)

{
	addLanguage(string("English"));
}

Attendant::Attendant(const Attendant& other) 
throw (const string&)
	: Person(other.getName(), other.getAge()), AirCrew(other), amountOfLanguages(0)

{
	for (int i = 0; i < other.getAmountOfLanguages(); i++)
	{
		addLanguage(*other.getLanguages()[i]);
	}
}

Attendant::~Attendant()
{
	for (int i = 0; i < amountOfLanguages; i++)
	{
		delete languages[i];
	}
}

AirCrew* Attendant::clone() const // for Prototype design pattern
{
	return new Attendant(*this);
}

void Attendant::addLanguage(const string& language) throw (const string&)
{
	if (language.empty())
	{
		throw string("# Language can't be empty #");
	}

	if (amountOfLanguages == MAX_NUMBER_OF_LANGUAGES) 
	{
		throw string("# Languages amount exceeded the max capacity #");
	}

	languages[amountOfLanguages++] = new string(language);
}

 void Attendant::toOs(ostream& out) const 
{
	out << "Languages spoken: " << getAmountOfLanguages() << endl;
	for (int i = 0; i < getAmountOfLanguages(); i++)
	{
		out << *getLanguages()[i] << "  " << endl;
	}
}

const string*const* Attendant::getLanguages() const
{
	return languages;
}