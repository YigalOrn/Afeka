#ifndef __ATTENDANT_H_
#define __ATTENDANT_H_
#include "AirCrew.h"
#include <ostream>
using namespace std;

class Attendant : public AirCrew
{
public: 
	static const int MAX_NUMBER_OF_LANGUAGES = 10;
private:
	char* languages[MAX_NUMBER_OF_LANGUAGES];
	int amountOfLAnguages;

public:
	Attendant(const Person& p, int seniority, double salary);
	~Attendant();

	bool addLanguage(const char* l);

	friend ostream& operator<<(ostream& out, const Attendant& a);

	const char** getLanguages() const;

private:
	Attendant(const Attendant& other);
	const Attendant& operator=(const Attendant& other);
};
#endif

