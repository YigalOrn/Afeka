#ifndef __FLIGHT_H_
#define __FLIGHT_H_

#include <iostream>
#include <typeinfo.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;


#include "Plane.h"
#include "Pilot.h"
#include "Date.h"
#include "AirCrew.h"
#include "FlightException.h"
#include "Iterator.h"

class Flight
{
	friend class Airline;
	friend class Array<Flight>;

	static int flightNumberCounter;
	int flightNumber;

	Date flightDate;
	string destination;
	
	Plane* plane; 
	
	vector<Seat> seatsVec;
	int amountOfTakenSeats;

	vector<AirCrew*> staffVec;
	int maxAmountOfStaff;
	
public:
	Flight( Plane* p, const Date& d, const string& dest, int maxAmountOfStaff=10) throw (FlightException);
	
	~Flight();

	Seat& getNextFreeSeat() throw (FlightException);

	friend ostream& operator<<(ostream& out, const Flight& f);
	
	// find staff member by a given string, if not there return null
	const AirCrew* const operator[](const string& name) const;

	void addStaffMember(AirCrew& ac) throw (FlightException);
	void removeStaffMember(AirCrew& ac) throw (FlightException);

	int getAmountOfTakenSeats() const;
	const string& getDestination() const;
	const Plane* const getPlane() const;
	const Date& getFlightDate() const;
	int getMaxAmountOfStaff() const;
	int getStaffAmount() const;
	int getSeatsAmount() const;
	int getFlightNumber() const;
	const vector<AirCrew*>& getStaff() const;
	const vector<Seat>& getSeats() const;
	const AirCrew& getCaptain() const;
	bool operator==(const Flight& flight) const;
	
	//void Flight::operator=(const Flight& f);

private:
	Flight(const Flight& f, Plane* airLinePlane);
	Flight();

	bool airCrewExistsInFlight(const AirCrew& airCrew) const;

	void setDestination(const string& dest) throw (FlightException);
};
#endif