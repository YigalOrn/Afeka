#include "Flight.h"

Flight::Flight(
	Plane* plane,
	const Date& d,
	const string& dest,
	int maxAmountOfStaff)
	throw (FlightException)
	:flightDate(d), maxAmountOfStaff(maxAmountOfStaff), destination(dest), flightNumber(flightNumberCounter++), amountOfTakenSeats(0)
{
	setDestination(dest);

	if (!plane)
	{
		throw FlightException(string("# Entered Invalid Plane object #"));
	}
	this->plane = plane;
	for (int i = 0; i < plane->getMaxNumOfSeats(); i++)
	{
		seatsVec.push_back(Seat());
	}
}

Flight::Flight(const Flight& f, Plane* airLinePlane) :
	flightDate(f.getFlightDate()),
	maxAmountOfStaff(f.getMaxAmountOfStaff()),
	flightNumber(f.getFlightNumber()),
	amountOfTakenSeats(f.getAmountOfTakenSeats()), seatsVec(f.getSeats())
{
	setDestination(f.getDestination());
	plane = airLinePlane;
	
	vector<AirCrew*>::const_iterator crewIter = f.getStaff().begin();
	for(; crewIter < f.getStaff().end(); ++crewIter)
	{
		
		staffVec.push_back( (*crewIter)->clone() );
		
	}
}
	
Flight::~Flight()
{
	// we don't free "vector<AirCrew*> staffVec" memory because the aircrew objects are referenced from airline crew vector(they are deleted in airline d'tor)
	staffVec.clear();
}

Flight::Flight() : flightDate(Date(10,10,1000021))
{
}

Seat& Flight::getNextFreeSeat() throw (FlightException)
{
	if (plane->getMaxNumOfSeats() <= amountOfTakenSeats)
	{
		throw FlightException(string("# No more seats available #"));
	}
	else
	{
		Seat& nextSeat = seatsVec.at(amountOfTakenSeats++);
		nextSeat.setSeat(Seat::TAKEN);
		return nextSeat;
	}
}

ostream& operator<<(ostream& os, const Flight& f)
{
	os << "______________________________________" << endl;
	os << "Flight Number: " << f.getFlightNumber() << endl;
	os << "Flight date: " << f.getFlightDate() << endl;
	os << "Destination: " << f.getDestination() << endl;
	os << "Plane: " << *f.getPlane() << endl;
	os << "Amount of seats taken: " << f.getAmountOfTakenSeats() << endl;
	os << "Flight's staff size: " << f.getStaffAmount() << endl;
	
	vector<AirCrew*>::const_iterator crewIter = f.staffVec.begin();
	for (; crewIter < f.staffVec.end(); ++crewIter)
	{
		os << *(*crewIter) << endl;
	}
	os << "______________________________________" << endl;
	return os;
}

// find staff member by a given string, if not there return null
const AirCrew* const Flight::operator[](const string& name) const
{
	
	vector<AirCrew*>::const_iterator crewIter = staffVec.begin();
	for (; crewIter < staffVec.end(); ++crewIter)
	{
		if ((*crewIter)->getName() == name)
		{
			return (*crewIter);
		}
	}
	return NULL;
}


void Flight::addStaffMember(AirCrew& ac) throw (FlightException)
{
	if (maxAmountOfStaff <= staffVec.size())
	{
		throw FlightException(string("# Staff amount exceeded the max amount #"));
	}
	// check if the airCrew member has a flight on the same date as the flight
	//using the inner class linked list in AirCrew
	if (ac.isDateAvailable(this->flightDate))
	{
		if (typeid(ac) == typeid(Pilot))
		{
			//cout << "Pilot - " << staffVec.size() << endl;
			staffVec.insert(staffVec.begin(), &ac);	
		}
		else
		{
			//cout << "Other - " << staffVec.size() <<  endl;
			staffVec.push_back(&ac);
		}
		ac.addDateToWorkingDatesList(this->getFlightDate());
	}
	else
	{
		throw FlightException(string("# Staff member already works on that date #"));
	}
}

void Flight::removeStaffMember(AirCrew& ac) throw (FlightException)
{
	if (typeid(ac) == typeid(Pilot))
	{
		staffVec.erase(staffVec.begin());
	}
	else
	{
		vector<AirCrew*>::iterator crewIter =
			find(staffVec.begin(), staffVec.end(), &ac);
		
		if (crewIter == staffVec.end())
		{
		
			string msg;
			stringstream sstm;
			sstm << "# Crew Member: " 
				<< ac.getName() 
				<< " does not exist in Flight Number:"
				<< this->getFlightNumber()
				<< " #";
			msg = sstm.str();
			throw FlightException(msg);
		}
		staffVec.erase(crewIter);
	}
	ac.removeDateFromWorkingDatesList(this->getFlightDate());
}

void Flight::setDestination(const string& dest) throw (FlightException)
{
	if (dest.empty())
	{
		throw FlightException(string("# Destination can't be NULL #"));
	}
	destination.assign(dest);
}

int Flight::getAmountOfTakenSeats() const
{
	return amountOfTakenSeats;
}

const string& Flight::getDestination() const
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

const vector<AirCrew*>& Flight::getStaff() const
{
	return staffVec;
}

const vector<Seat>& Flight::getSeats() const
{
	return seatsVec;
}

int Flight::getMaxAmountOfStaff() const
{
	return maxAmountOfStaff;
}

int Flight::getStaffAmount() const
{
	return staffVec.size();
}

int Flight::getSeatsAmount() const
{
	return seatsVec.size();
}

bool Flight::airCrewExistsInFlight(const AirCrew& ac) const
{
	vector<AirCrew*>::const_iterator crewIter =
		find(staffVec.begin(), staffVec.end(), &ac);
	if (crewIter != staffVec.end())
	{
		return true;
	}
	return false;
}

bool Flight::operator==(const Flight& flight) const
{
	return this->getFlightNumber() == flight.getFlightNumber();
}

const AirCrew& Flight::getCaptain() const
{
	return *staffVec.at(0);
}

int Flight::getFlightNumber() const
{
	return flightNumber;
}

int Flight::flightNumberCounter = 1;

