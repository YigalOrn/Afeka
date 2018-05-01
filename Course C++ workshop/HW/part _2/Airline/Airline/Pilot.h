#ifndef __PILOT_H_
#define __PILOT_H_

#include "AirCrew.h"
#include "SpecialEmployee.h"
#include <ostream>
using namespace std;


class Pilot : public AirCrew, public SpecialEmployee
{
	int monthlyFlightHours;

public:
	Pilot(const Person& p, int seniority, double salary, int numOfFreeFlightsInYear);

	friend ostream& operator<<(ostream& out, const Pilot& p);

	double getAvgSalaryPerHour();
	int getMonthlyFlightHours() const;

private:
	Pilot(const Pilot& p);
	const Pilot& operator=(const Pilot& p);

};
#endif