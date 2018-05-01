#include <typeinfo.h>
#include <iostream>
#include <cstring>
using namespace std;

#include "Flight.h"


Flight::Flight(
	Plane* plane,
	const Date& d,
	const char* dest,
	int maxAmountOfStaff) 
	throw (FlightException)
	:flightDate(d), maxAmountOfStaff(maxAmountOfStaff), amountOfTakenSeats(0), staffAmount(0), destination(0), flightNumber(flightNumberCounter++)
{
	setDestination(dest);

	if (!plane)
	{
		throw FlightException("# Entered Invalid Plane object #");
	}
	this->plane = plane;
	seats = new Seat[plane->getMaxNumOfSeats()];
	staff = new AirCrew*[maxAmountOfStaff];
}

Flight::Flight(const Flight& f) :
	flightDate(f.getFlightDate()),
	maxAmountOfStaff(f.getMaxAmountOfStaff()),
	amountOfTakenSeats(f.getAmountOfTakenSeats()),
	staffAmount(f.getStaffAmount()),
	destination(0),
	flightNumber(f.getFlightNumber())
{

	setDestination(f.getDestination());
	plane = new Plane(*f.getPlane());
	seats = new Seat[plane->getMaxNumOfSeats()];
	staff = new AirCrew*[maxAmountOfStaff];
	for (int i = 0; i < staffAmount; i++)
	{
		staff[i] = (f.getStaff()[i])->clone();
	}
}

Flight::~Flight()
{
	delete[]destination;
	delete[]seats;
	delete[]staff;
}


Seat& Flight::getNextFreeSeat() throw (FlightException)
{
	if (plane->getMaxNumOfSeats() <= amountOfTakenSeats)
	{
		throw FlightException("# No more seats available #");
	}
	else
	{
		return seats[amountOfTakenSeats++];
	}
}

ostream& operator<<(ostream& os, const Flight& f)
{
	os << "Flight Number: " << f.getFlightNumber() << endl;
	os << "Flight date: " << f.getFlightDate() << endl;
	os << "Destination: " << f.getDestination() << endl;
	os << "Plane: " << *f.getPlane() << endl;
	os << "Amount of seats taken: " << f.getAmountOfTakenSeats() << endl;
	os << "Flight's staff size: " << f.getStaffAmount() << endl;
	for (int i = 0; i < f.getStaffAmount(); i++)
	{
		os << *f.getStaff()[i] << endl;
	}
	return os;
}

// find staff member by a given string, if not there return null
const AirCrew* const Flight::operator[](const char* name) const
{
	for (int i = 0; i < staffAmount; i++)
	{
		if (strcmp(staff[i]->getName(), name) == 0)
		{
			return staff[i];
		}
	}
	return NULL;
}


void Flight::addStaffMember(AirCrew& ac, int index) throw (FlightException)
{
	if (maxAmountOfStaff <= staffAmount)
	{
		throw FlightException("# Staff amount exceeded the max amount #");
	}
	// check if the airCrew member has a flight on the same date as the flight
	//using the inner class linked list in AirCrew
	if (ac.isDateAvailable(this->flightDate))
	{
		//shift then add
		for (int i = staffAmount; i > index; i--)
		{
			this->staff[i] = this->staff[i-1];
		}
		
		staffAmount++;
		this->staff[index] = &ac;
		ac.addDateToWorkingDatesList(this->getFlightDate());
	}
	else
	{
		throw FlightException("# Staff member already works on that date #");
	}
}

void Flight::addStaffMember(AirCrew& ac) 	throw (FlightException)
{
	if (maxAmountOfStaff <= staffAmount)
	{
		throw FlightException("# Staff amount exceeded the max amount #");
	}

	// check if the airCrew member has a flight on the same date as the flight
	//using the inner class linked list in AirCrew
	if (ac.isDateAvailable(this->flightDate))
	{
		this->staff[staffAmount++] = &ac;
		ac.addDateToWorkingDatesList(this->getFlightDate());
	}
	else
	{
		throw FlightException("# Staff member already works on that date #");
	}
}

void Flight::removeStaffMember(AirCrew& ac) throw (FlightException)
{
	// free ac's Date
	if (typeid(ac) == typeid(Pilot))
	{
		//save zero index in array for pilot
		staff[0] = NULL;
		for (int i = staffAmount-1; i > 0; i--)
		{
			this->staff[i-1] = this->staff[i];
		}
	}
	else
	{
		int i;
		for (i = 1; i < staffAmount && !(ac == *staff[i]); i++);
		if (i == staffAmount)
		{
			char space[10];
			char msg[100];
			strcpy(msg, "Crew Member: ");
			strcat(msg, ac.getName());
			strcat(msg, " does not exist in Flight Number:");
			strcat(msg, itoa(this->getFlightNumber(), space, 10));
			throw FlightException(msg);
		}
		// closing the gap
		staff[i] = staff[staffAmount - 1];
		staff[staffAmount - 1] = NULL;
	}
	ac.removeDateFromWorkingDatesList(this->getFlightDate());
	this->staffAmount--;
}

void Flight::setDestination(const char* dest) throw (FlightException)
{
	if (!dest)
	{
		throw FlightException("# Destination can't be NULL #");
	}
	delete[]destination;
	destination = new char[strlen(dest) + 1];
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

const Plane* const Flight::getPlane() const
{
	return plane;
}

const Date& Flight::getFlightDate() const
{
	return flightDate;
}

const AirCrew*const* Flight::getStaff() const
{
	return staff;
}

int Flight::getMaxAmountOfStaff() const
{
	return maxAmountOfStaff;
}

int Flight::getStaffAmount() const
{
	return staffAmount;
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
	return this->getFlightNumber() == flight.getFlightNumber();
}

const AirCrew& Flight::getCaptain() const
{
	return *staff[0];
}

int Flight::getFlightNumber() const
{
	return flightNumber;
}

int Flight::flightNumberCounter = 1;











