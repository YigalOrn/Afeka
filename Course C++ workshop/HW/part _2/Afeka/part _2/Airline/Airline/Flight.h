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
	
	Plane* plane; 
	Seat* seats;
	int amountOfTakenSeats;

	AirCrew** staff;
	int maxAmountOfStaff;
	int staffAmount;

public:
	Flight(Plane* p, const Date& d, const char* dest, Pilot* captain, 
		int maxAmountOfStaff=10);
	~Flight();

	Seat& getNextFreeSeat();

	friend ostream& operator<<(ostream& out, const Flight& f);
	// find staff member by a given string, if not there return null
	const AirCrew* const operator[](const char* name) const; 

	bool addStaffMember(AirCrew& ac);
	bool removeStaffMember(const AirCrew& ac);

	

	int getAmountOfTakenSeats() const;
	const char* getDestination()const; 
	const Date& getFlightDate() const;

	const AirCrew*const* getStaff() const;

	bool operator==(const Flight& flight) const;

private:
	Flight(const Flight& f);
	const Flight& operator=(const Flight& f);
	bool airCrewExistsInFlight(const AirCrew& airCrew) const;

	//void setFlightDate(const Date& flightDate);  LAMA ZRIHIM ET ZE ??
	void setDestination(const char* dest);
};
#endif