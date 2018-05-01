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
	
	for (int i = 0; i < numberOfCustomers; i++)
	{
		delete customers[i];
	}
	delete[] customers; 
	
		for (int i = 0; i < numberOfCrewMembers; i++)
	{
		delete crew[i];
	}
	delete[] crew;
	
	for (int i = 0; i < numberOfOrders; i++)
	{
		delete orders[i];
	}
	delete[] orders;
}

void Airline::setName(const char* name) throw(const char*)
{
	if (name)
	{
		airlineName = new char[strlen(name)];
		strcpy(airlineName, name);
	}
	else
	{
		throw("# Exception: name is NULL");
	}
}

bool Airline::addFlight(const Flight& f)
{
	int flightIndex = getIndex(flights, f, numberOfFlights);

	if ( (numberOfFlights >= maxNumberOfFlights) || (flightIndex !=-1) )
	{
		return false;
	}
	else
	{
		flights[numberOfFlights++] = new Flight(f);
	    //check alloc, use exception
		return true;
	}
}

bool Airline::addPlane(const Plane& p)
{
	int planeIndex = getIndex(planes, p, numberOfPlanes);

	if (numberOfPlanes >= maxNumberOfPlanes || (planeIndex !=-1))
	{
		return false;
	}
	else
	{
		planes[numberOfPlanes++] = new Plane(p);
		return true;
	}
}

bool Airline::addCustomer(const Customer& c)
{
	int customerIndex = getIndex(customers, c, numberOfPlanes);

	if (numberOfCustomers >= maxNumberOfCustomers || (customerIndex !=-1))
	{
		return false;
	}
	else
	{
		customers[numberOfCustomers++] = new Customer(c);
		return true;
	}
}

bool Airline::addCrewMember(const AirCrew& ac)
{
	int crewMemberIndex = getIndex(crew, ac, numberOfCrewMembers);

	if (numberOfCrewMembers >= maxNumberOfCrewMembers || (crewMemberIndex !=-1))
	{
		return false;
	}
	else
	{
		crew[numberOfCrewMembers++] = new AirCrew(ac);
		return true;
	}
}

bool Airline::addOrder(const Order& o)
{
	int orderIndex = getIndex(orders, o, numberOfOrders);

	if (numberOfOrders >= maxNumberOfOrders || (orderIndex !=-1))
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
	return out << "DONT FORGET TO IMPLEMENT OPERATOR<< IN AIRLINE.CPP" << endl;
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
	int flightIndex = getIndex(flights, f, numberOfFlights);
	
	if (flightIndex != -1) 
	{
		//add new crew member
		return flights[flightIndex]->addStaffMember(ac);
	}
}

bool Airline::removeStaffMemberFromFlight(const AirCrew& ac, const Flight& f)
{
	int flightIndex = getIndex(flights, f, numberOfFlights);
	if (flightIndex != -1)
	{
		return (*flights[flightIndex]).removeStaffMember(ac);
	}
	return false;
}

Ticket Airline::createTicketForFlight(Flight& f) 
{
	int flightIndex = getIndex(flights, f, numberOfFlights);
	if(flightIndex==-1)
	{
		//throw exception
	}
	return Ticket(f, f.getNextFreeSeat(), f.getFlightDate());
}

bool Airline::cancelOrder(const Order& o)
{
	int orderIndex = getIndex(orders, o, numberOfOrders);
	if (orderIndex != -1)
	{
		delete orders[orderIndex];
		return true;
	}
	return false;
}

template<typename T>
int Airline::getIndex(T** arr, const T& obj, int currSize) const
{
	if (!arr)
	{
		return -1;
	}

	for (int i = 0; i < currSize; i++)
	{
		cout << "IMPLEMENT OPERATOR== !!!!! in Flight, Plane, Customer,...." << endl;
		//check if implementation belongs here!, operator=
		/*if (arr[i] == obj)
		{
			return i;
		}*/
	}
	return -1;
}

