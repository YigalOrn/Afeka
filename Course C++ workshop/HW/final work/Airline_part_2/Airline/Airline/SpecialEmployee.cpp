#include <iostream>
using namespace std;

#include "SpecialEmployee.h"

SpecialEmployee::SpecialEmployee(const Person& p, int numberOfFreeFlights) :
Person(p), numberOfFreeFlightsPerYear(numberOfFreeFlights)
{
}

SpecialEmployee::SpecialEmployee(const SpecialEmployee& se) : Person(se), numberOfFreeFlightsPerYear(se.getNumberOfFreeFlightsPerYear())
{
}

SpecialEmployee::~SpecialEmployee() {}

int SpecialEmployee::getNumberOfFreeFlightsPerYear() const 
{
	return numberOfFreeFlightsPerYear;
}

ostream& operator<<(ostream& out, const SpecialEmployee& se) 
{
	out << "Special Employee name : " << se.getName() << endl;
	out << "Special Employee age : " << se.getAge() << endl;
	out << "Number of free flights per year : " << se.getNumberOfFreeFlightsPerYear() << endl;
	return out;
}











