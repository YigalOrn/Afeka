#include <iostream>
#include <cstring>
using namespace std;


#include "Airline.h"


Airline::Airline(
	const char* name,
	int maxNumberOfFlights,
	int maxNumberOfPlanes,
	int maxNumberOfCustomers,
	int maxNumberOfCrewMembers,
	int maxNumberOfOrders) :
	maxNumberOfFlights(maxNumberOfFlights),
	maxNumberOfPlanes(maxNumberOfPlanes),
	maxNumberOfCustomers(maxNumberOfCustomers),
	maxNumberOfCrewMembers(maxNumberOfCrewMembers),
	maxNumberOfOrders(maxNumberOfOrders)
{
	setName(name);

	//check alloc, use exception
	flights = new Flight*[maxNumberOfFlights];
	planes = new Plane*[maxNumberOfPlanes];
	customers = new Customer*[maxNumberOfCustomers];
	crew = new AirCrew*[maxNumberOfCrewMembers];
	orders = new Order*[maxNumberOfOrders];

	initNumberFields();
}

void Airline::initNumberFields()
{
	numberOfFlights = 0;
	numberOfPlanes = 0;
	numberOfCustomers = 0;
	numberOfCrewMembers = 0;
	numberOfOrders = 0;
}

Airline::~Airline()
{
	delete[] airlineName;

	for (int i = 0; i < numberOfFlights; i++)
	{
		delete flights[i];
	}
	delete[] flights;

	for (int i = 0; i < numberOfPlanes; i++)
	{
		delete planes[i];
	}
	delete[] planes;

	delete[] customers; // only saves addresses, Customer has no copy c'tor

	delete[] crew;

	for (int i = 0; i < numberOfOrders; i++)
	{
		delete orders[i];
	}
	delete[] orders;
}

void Airline::setName(const char* name)
{
	if (name)
	{
		airlineName = new char[strlen(name)];
		strcpy(airlineName, name);
	}
	else
	{
		//throw exception
	}
}

bool Airline::addFlight(Flight& f)
{
	if (numberOfFlights >= maxNumberOfFlights)
	{
		return false;
	}
	else
	{
		flights[numberOfFlights++] = new Flight(f);//Flight has copy c'tor
	//check alloc and then return
		return true;
	}
}

bool Airline::addPlane(Plane& p)
{
	if (numberOfPlanes >= maxNumberOfPlanes)
	{
		return false;
	}
	else
	{
		planes[numberOfPlanes++] = new Plane(p);//Plane has copy c'tor
		return true;
	}
}

bool Airline::addCustomer(Customer& c)
{
	if (numberOfCustomers >= maxNumberOfCustomers)
	{
		return false;
	}
	else
	{
		customers[numberOfCustomers++] = &c;
		return true;
	}
}

bool Airline::addCrewMember(AirCrew& ac)
{
	if (numberOfCrewMembers >= maxNumberOfCrewMembers)
	{
		return false;
	}
	else
	{
		crew[numberOfCrewMembers++] = &ac;
		return true;
	}
}

bool Airline::addOrder(Order& o)
{
	if (numberOfOrders >= maxNumberOfOrders)
	{
		return false;
	}
	else
	{
		orders[numberOfOrders++] = new Order(o);
		return true;
	}
}

ostream& operator<<(ostream& out, const Airline& a)
{
}


Flight*const*  Airline::getFlights() const
{
	return flights;
}

int Airline::getFlightsAmount() const
{
	return numberOfFlights;
}

Plane*const* Airline::getPlanes() const
{
	return planes;
}


int Airline::getPlanesAmount() const
{
	return numberOfPlanes;
}

Customer*const* Airline::getCustomers() const
{
	return customers;
}

int Airline::getCustomersAmount() const
{
	return numberOfCustomers;
}

AirCrew*const* Airline::getAirCrews() const
{
	return crew;
}


int Airline::getAirCrewsAmount() const
{
	return numberOfCrewMembers;
}

Order*const* Airline::getOrders() const
{
	return orders;
}

int Airline::getOrdersAmount() const
{
	return numberOfOrders;
}

int Airline::getAmountOfTicketsInFlight(const Flight& f) const
{
	return f.getAmountOfTakenSeats();
}



bool Airline::addStaffMemberToFlight(AirCrew& ac, Flight& f)
{
	//airline has its own crew...or at least it has a crew array

	for (int i = 0; i < numberOfFlights; i++)
	{
		if ((*flights[i]) == f) 
		{
			//add new crew member
			flights[i]->addStaffMember(ac);
			break;
		}
	}
}

bool Airline::removeStaffMemberFromFlight(const AirCrew& ac, const Flight& f)
{
}

Ticket Airline::createTicketForFlight(const Flight& f) const
{
}

bool Airline::cancelOrder(const Order& o)
{
}


