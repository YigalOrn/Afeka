#ifndef __ATTENDANT_H_
#define __ATTENDANT_H_

//#define _CRT_SECURE_NO_WARNINGS

#include "AirCrew.h"
#include <iostream>
#include <string>

using namespace std;

class Attendant : public AirCrew
{
public: 
	static const int MAX_NUMBER_OF_LANGUAGES = 10;

	Attendant(const Person& p, int seniority, double salary) 
		throw (const string&);
	virtual ~Attendant();

	virtual AirCrew* clone() const; // for Prototype design pattern

	friend ostream& operator<<(ostream& out, const Attendant& a);
	virtual void toOs(ostream& out) const;

	const string*const* getLanguages() const;
	int getAmountOfLanguages() const { return amountOfLanguages; }
	void addLanguage(const string& language) throw (const string&);

private:
	string* languages[MAX_NUMBER_OF_LANGUAGES];
	int amountOfLanguages;

	Attendant(const Attendant& other) throw (const string&);
	const Attendant& operator=(const Attendant& other);
};
#endif

