#include "Pilot.h"

Pilot::Pilot(const Person& p, int seniority, double salary, int numberOfFreeFlightsPerYear, int monthlyFlightHours) : Person(p), AirCrew(p, seniority, salary), SpecialEmployee(p, numberOfFreeFlightsPerYear), monthlyFlightHours(monthlyFlightHours) {}

Pilot::Pilot(const Pilot& p) : Person(p.getName(), p.getAge()), AirCrew(p), SpecialEmployee(p),
monthlyFlightHours(p.getMonthlyFlightHours())
{
}

AirCrew* Pilot::clone() const // for Prototype design pattern
{
	return new Pilot(*this);
}

ostream& operator<<(ostream& out, const Pilot& p)
{
	out << "Pilot name: " << p.getName() << endl;
	out << "Pilot age: " << p.getAge() << endl;
	out << "Seniority: " << p.getSeniority() << " , Salary: " << p.getSalary() << endl;
	out << "Number of free flights per year: " << p.getNumberOfFreeFlightsPerYear() << endl;
	out << "Monthly flying hours: " << p.getMonthlyFlightHours() << endl;
	return out;
}

void Pilot::toOs(ostream& out) const 
{
	out << "Number of free flights per year: " << getNumberOfFreeFlightsPerYear() << endl;
	out << "Monthly flying hours: " << getMonthlyFlightHours() << endl;
}

double Pilot::getAvgSalaryPerHour()
{
	return salary / monthlyFlightHours;
}

int Pilot::getMonthlyFlightHours() const
{
	return monthlyFlightHours;
}