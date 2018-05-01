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
	int maxNumberOfOrders) 
	throw(AirLineException)
	:maxNumberOfFlights(maxNumberOfFlights),
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

void Airline::setName(const char* name) throw(AirLineException)
{
	if (name)
	{
		airlineName = new char[strlen(name)+1];
		strcpy(airlineName, name);
	}
	else
	{
		throw AirLineException("# Airline Name cannot be NULL #");
	}
}

void Airline::addFlight(const Flight& f) throw(AirLineException)
{

	if (numberOfFlights >= maxNumberOfFlights)
	{
		throw AirLineException("# Number of flights exceeded its max capacity #");
	}

	try
	{
	getIndex(flights, f, numberOfFlights);
	}
	catch (AirLineException ex)
	{
		flights[numberOfFlights] = new Flight(f);
		//check alloc
		numberOfFlights++;
	}
}

void Airline::addPlane(const Plane& p) throw (AirLineException)
{

	if (numberOfPlanes >= maxNumberOfPlanes)
	{
		throw AirLineException("# Number of planes exceeded its max capacity #");
	}

	try
	{
		getIndex(planes, p, numberOfPlanes);
	}
	catch (AirLineException ex)
	{
		planes[numberOfPlanes] = new Plane(p);
		//check alloc
		numberOfPlanes++;
	}
}

void Airline::addCustomer(const Customer& c) throw (AirLineException)
{

	if (numberOfCustomers >= maxNumberOfCustomers)
	{
		throw AirLineException("# Number of customers exceeded its max capacity #");
	}

	try
	{
		getIndex(customers, c, numberOfCustomers);
	}
	catch (AirLineException ex)
	{
		customers[numberOfCustomers] = new Customer(c);
	//check alloc
		numberOfCustomers++;
	}	
}

void Airline::addCrewMember(const AirCrew& ac) throw (AirLineException)
{

	if (numberOfCrewMembers >= maxNumberOfCrewMembers)
	{
		throw AirLineException("# Number of crew members exceeded its max capacity #");
	}

	try
	{
	getIndex(crew, ac, numberOfCrewMembers);
	}
	catch (AirLineException ex)
	{
		crew[numberOfCrewMembers] = ac.clone();
	//check alloc
		numberOfCrewMembers++;
	}
}

int Airline::addOrder(const Date& date, const Customer& cust)
throw (AirLineException)
{
	if (numberOfOrders >= maxNumberOfOrders)
	{
		throw AirLineException("# Number of orders exceeded its max capacity #");
	}
	int custIndex = getIndex(customers, cust, numberOfCustomers);//THROWS
	orders[numberOfOrders] = new Order(date, customers[custIndex]);
	//check alloc
	numberOfOrders++;
	return orders[numberOfOrders - 1]->getOrderId();
}

Order* Airline::getOrder(int orderId) throw (AirLineException)
{
	for (int i = 0; i < numberOfOrders; i++)
	{
		if (orders[i]->getOrderId() == orderId) 
		{
			return orders[i];
		}
	}

	char space[10];
	char msg[150];
	strcpy(msg, "Order with ID: ");
	strcat(msg, itoa(orderId, space, 10));
	strcat(msg, " does not exist");
	throw AirLineException(msg);
	return NULL;
}

ostream& operator<<(ostream& out, const Airline& a)
{
	out << "Airline name : " << a.getAirlineName() << endl;
	out << "Planes : " << endl;
	
	for (int i = 0; i < a.getPlanesAmount(); i++)
	{
		out << "------------------------------" << endl;
		out << *a.getPlanes()[i] << endl;
	}
	out << "---------------------------------------------------------------------" << endl;
	out << "Flights : " << endl;
	for (int i = 0; i < a.getFlightsAmount(); i++)
	{
		out << "------------------------------" << endl;
		out << *a.getFlights()[i] << endl;
	}
	out << "---------------------------------------------------------------------" << endl;
	out << "AirCrew size: " << a.getAirCrewsAmount() << endl;
	out << "AirCrews : " << endl;
	for (int i = 0; i < a.getAirCrewsAmount(); i++)
	{
		out << "------------------------------" << endl;
		out << *a.getAirCrews()[i] << endl;
	}
	out << "---------------------------------------------------------------------" << endl;
	out << "Orders : " << endl;
	for (int i = 0; i < a.getOrdersAmount(); i++)
	{
		out << "------------------------------" << endl;
		out << *a.getOrders()[i] << endl;
	}
	out << "---------------------------------------------------------------------" << endl;
	out << "Customers : " << endl;
	for (int i = 0; i < a.getCustomersAmount(); i++)
	{
		out << "------------------------------" << endl;
		out << *a.getCustomers()[i] << endl;
	}

	return out;
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

void Airline::addStaffMemberToFlight(AirCrew& ac, Flight& f) 
throw (AirLineException, FlightException)
{
	int flightIndex = getIndex(flights, f, numberOfFlights);
	int staffMemberIndex = getIndex(crew, ac, numberOfCrewMembers);
	//add new crew member
	
	if (typeid(ac) == typeid(Pilot)) 
	{
		flights[flightIndex]->addStaffMember(*crew[staffMemberIndex], 0);
	}
	else 
	{
		flights[flightIndex]->addStaffMember(*crew[staffMemberIndex]);//THROWS
	}
}



void Airline::removeStaffMemberFromFlight(AirCrew& ac, const Flight& f)
throw (AirLineException, FlightException)
{
	int flightIndex = getIndex(flights, f, numberOfFlights);
	int staffMemberIndex = getIndex(crew, ac, numberOfCrewMembers);
	//remove crew member
	(*flights[flightIndex]).removeStaffMember(ac);
}

const Ticket Airline::createTicketForFlight(Flight& f)
throw (AirLineException, FlightException)
{
	int flightIndex = getIndex(flights, f, numberOfFlights);
	return Ticket(*flights[flightIndex], 
		(*flights[flightIndex]).getNextFreeSeat(), 
		(*flights[flightIndex]).getFlightDate());
}

void Airline::cancelOrder(const Order& o) throw(AirLineException)
{
	int orderIndex = getIndex(orders, o, numberOfOrders);
	delete orders[orderIndex];
	numberOfOrders--;
}

