#ifndef __FLIGHT_H_
#define __FLIGHT_H_

#include <iostream>
using namespace std;


#include "Plane.h"
#include "Pilot.h"
#include "Date.h"
#include "AirCrew.h"
#include "FlightException.h"


class Flight
{
	friend class Airline;

	static int flightNumberCounter;
	int flightNumber;

	Date flightDate;
	char* destination;
	
	Plane* plane; 
	Seat* seats;
	int amountOfTakenSeats;

	AirCrew** staff;
	int maxAmountOfStaff;
	int staffAmount;

public:
	Flight( Plane* p, const Date& d, const char* dest, int maxAmountOfStaff=10) throw (FlightException);
	
	~Flight();

	Seat& getNextFreeSeat() throw (FlightException);

	friend ostream& operator<<(ostream& out, const Flight& f);
	// find staff member by a given string, if not there return null
	const AirCrew* const operator[](const char* name) const; 

	void addStaffMember(AirCrew& ac) throw (FlightException);
	void addStaffMember(AirCrew& ac, int index) throw (FlightException);
	void removeStaffMember(AirCrew& ac) throw (FlightException);

	int getAmountOfTakenSeats() const;
	const char* getDestination() const; 
	const Plane* const getPlane() const;
	const Date& getFlightDate() const;
	int getMaxAmountOfStaff() const;
	int getStaffAmount() const;
	int getFlightNumber() const;
	const AirCrew*const* getStaff() const;
	const AirCrew& getCaptain() const;
	bool operator==(const Flight& flight) const;

private:
	Flight(const Flight& f);

	const Flight& operator=(const Flight& f);
	bool airCrewExistsInFlight(const AirCrew& airCrew) const;

	void setDestination(const char* dest) throw (FlightException);
};
#endif