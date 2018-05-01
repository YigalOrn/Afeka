#ifndef __FLIGHT_H_
#define __FLIGHT_H_

#include "Plane.h"
#include "Pilot.h"
#include "Date.h"
#include "AirCrew.h"

#include <ostream>
using namespace std;

class Flight
{
	Date flightDate;
	char* destination;
	
	Plane* p; 
	Seat* seats;
	int amountOfTakenSeats;

	AirCrew** staff;
	int maxAmountOfStaff;
	int staffAmount;

public:
	Flight(Plane* p, const Date& d, const char* dest, Pilot* captain, int maxAmountOfStaff=10);
	Flight(const Flight& f);
	~Flight();

	const Flight& operator=(const Flight& f);

	Seat& getNextFreeSeat();

	friend ostream& operator<<(ostream& out, const Flight& f);
	const AirCrew& operator[](const char* name) const; // find staff member by a given string

	bool addStaffMember(AirCrew& ac);
	bool removeStaffMember(const AirCrew& ac);

	void setDate(const Date& d);
	void setDestination(const char* dest);

	int getAmountOfTakenSeats() const;
	const char* getDestination()const; 
	const Date& getFlightDate() const;

	const AirCrew** getStaff() const;


	bool operator==(const Flight& d) const;

};
#endif