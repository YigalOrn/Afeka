#ifndef __SPECIAL_EMPLOYEE_H_
#define __SPECIAL_EMPLOYEE_H_

#include "Person.h"
#include <iostream>
using namespace std;

class SpecialEmployee : virtual public Person
{
protected:
	int numberOfFreeFlightsPerYear;

	SpecialEmployee(const Person& p, int numberOfFreeFlights);
	SpecialEmployee(const SpecialEmployee& se);
	const SpecialEmployee& operator=(const SpecialEmployee& other);

public:
	virtual ~SpecialEmployee();

	int getNumberOfFreeFlightsPerYear() const;

	friend ostream& operator<<(ostream& out, const SpecialEmployee& se);
};
#endif
