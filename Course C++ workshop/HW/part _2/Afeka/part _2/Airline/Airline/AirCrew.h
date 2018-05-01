#ifndef __AIR_CREW_H_
#define __AIR_CREW_H_

#include "Person.h"
#include <ostream>
using namespace std;

class AirCrew : virtual public Person
{
protected:
	int seniority;
	double salary;

	AirCrew(const Person& p, int seniority, double salary);
	AirCrew(const AirCrew& other);
	const AirCrew& operator=(const AirCrew& other);

public:
	virtual ~AirCrew();
	
	friend ostream& operator<<(ostream& out, const AirCrew& ac);

	void setSalary(double salary);
	void setSeniority(int seniority);

	double getSalary() const;
	int getSeniority() const;

	bool operator==(const AirCrew& airCrew) const;
};
#endif