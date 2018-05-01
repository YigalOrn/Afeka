#ifndef __ATTENDANT_H_
#define __ATTENDANT_H_

#include "AirCrew.h"
#include <iostream>
using namespace std;

class Attendant : public AirCrew
{
public: 
	
	static const int MAX_NUMBER_OF_LANGUAGES = 10;

	Attendant(const Person& p, int seniority, double salary) 
		throw (const char*);
	virtual ~Attendant();

	virtual AirCrew* clone() const; // for Prototype design pattern

	void addLanguage(const char* language) throw (const char*);

	friend ostream& operator<<(ostream& out, const Attendant& a);

	virtual void toOs(ostream& out) const;

	const char*const* getLanguages() const;

	int getAmountOfLanguages() const { return amountOfLanguages; }

private:

	char* languages[MAX_NUMBER_OF_LANGUAGES];
	int amountOfLanguages;

	Attendant(const Attendant& other) throw (const char*);
	const Attendant& operator=(const Attendant& other);
};
#endif

