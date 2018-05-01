#include <ostream>
#include <string>
using namespace std;

#include "Flight.h"

Flight::Flight(
	Plane* plane, 
	const Date& d, 
	const char* dest, 
	Pilot* captain, 
	int maxAmountOfStaff=10) : flightDate(d), maxAmountOfStaff(maxAmountOfStaff), 
	amountOfTakenSeats(0), staffAmount(0), destination(0)
{

	setDestination(dest);

	if (!plane)
	{
		// throw exception
	}
	this->plane = plane;
	seats = new Seat[plane->getMaxNumOfSeats()];
	staff = new AirCrew*[maxAmountOfStaff];
}

Flight::~Flight()
{
	delete []destination;
	delete []seats;
	// WHAT ABOUT STAFFFF????? address?? copied object ??
	delete []staff;
}


Seat& Flight::getNextFreeSeat()
{
	if (plane->getMaxNumOfSeats <= amountOfTakenSeats)
	{
		// throws exc
	}
	else
	{
		return seats[amountOfTakenSeats++];
	}
}

ostream& operator<<(ostream& os, const Flight& f)
{
	return os << "Dont forget to impl.  operator<< in FLIGHT" << endl;
}

// find staff member by a given string, if not there return null
const AirCrew* const Flight::operator[](const char* name) const
{
	for (int i = 0; i < staffAmount; i++)
	{
		if(strcmp(staff[i]->getName(), name) == 0)
		{
			return staff[i]; 
		}
	}
	return NULL;
}

bool Flight::addStaffMember(AirCrew& ac)
{
	// Adam? Ma kore po ?
	// USE airCrewExistsInFlight here
}

bool Flight::removeStaffMember(const AirCrew& ac)
{
	// Adam? Ma kore po ?
	// USE airCrewExistsInFlight here
}

/*
void Flight::setFlightDate(const Date& flightDate)
{
	this->flightDate = flightDate;
}*/

void Flight::setDestination(const char* dest)
{
	if (!dest)
	{
		// throw exception		
	}
	delete []destination;
	destination = new char[strlen(dest)+1];
	strcpy(destination, dest);
}

int Flight::getAmountOfTakenSeats() const
{
	return amountOfTakenSeats;
}

const char* Flight::getDestination()const
{
	return destination;
}

const Date& Flight::getFlightDate() const
{
	return flightDate;
}

const AirCrew*const* Flight::getStaff() const
{
	return staff;
}

bool Flight::airCrewExistsInFlight(const AirCrew& airCrew) const
{
	for (int i = 0; i < staffAmount; i++)
	{
		if (*staff[i] == airCrew)
		{
			return true;
		}
	}
	return false;
}

bool Flight::operator==(const Flight& flight) const
{
	return this == &flight;
}














