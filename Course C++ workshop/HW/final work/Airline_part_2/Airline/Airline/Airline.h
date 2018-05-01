#ifndef __AIRLINE_H_
#define __AIRLINE_H_

#include "AirCrew.h"
#include "Flight.h"
#include "Plane.h"
#include "Customer.h"
#include "Order.h"
#include "Ticket.h"
#include "Pilot.h"
#include "Attendant.h"
#include "AirLineException.h"
#include "FlightException.h"

#include <iostream>
using namespace std;

class Airline
{
	char* airlineName;

	Flight** flights;
	int maxNumberOfFlights;
	int numberOfFlights;

	Plane** planes;
	int maxNumberOfPlanes;
	int numberOfPlanes;

	Customer** customers;
	int maxNumberOfCustomers;
	int numberOfCustomers;

	AirCrew** crew;
	int maxNumberOfCrewMembers;
	int numberOfCrewMembers;

	Order** orders;
	int maxNumberOfOrders;
	int numberOfOrders;

public:
	Airline(const char* name, int maxNumberOfFlights = 50, int maxNumberOfPlanes = 20, int maxNumberOfCustomers = 200,
		int maxNumberOfCrewMembers = 30, int maxNumberOfOrders = 300) 
		throw(AirLineException);

	~Airline();

	void setName(const char* name) throw(AirLineException);

	void addFlight(const Flight& f) throw(AirLineException);
	void addPlane(const Plane& p) throw(AirLineException);
	void addCustomer(const Customer& c) throw(AirLineException);
	void addCrewMember(const AirCrew& ac) throw(AirLineException);
	int addOrder(const Date& date, const Customer& cust) 
		throw(AirLineException);

	Order* getOrder(int orderId);

	friend ostream& operator<<(ostream& out, const Airline& a);

	const char* getAirlineName() const { return airlineName;  }

	Flight*const*  getFlights() const;
	int getFlightsAmount() const;

	Plane*const* getPlanes() const;
	int getPlanesAmount() const;

	Customer*const* getCustomers() const;
	int getCustomersAmount() const;

	AirCrew*const* getAirCrews() const;
	int getAirCrewsAmount() const;

	Order*const* getOrders() const;
	int getOrdersAmount() const;

	int getAmountOfTicketsInFlight(const Flight& f) const;

	void addStaffMemberToFlight(AirCrew& ac, Flight& f) 
		throw (AirLineException, FlightException);
	void removeStaffMemberFromFlight(AirCrew& ac, const Flight& f)
		throw (AirLineException, FlightException);
	const Ticket createTicketForFlight(Flight& f)
		throw (AirLineException, FlightException);
	void cancelOrder(const Order& o)
		throw(AirLineException);

private:
	Airline(const Airline& other);
	const Airline& operator=(const Airline& other);
	void initNumberFields();

	template<typename T>
	int getIndex(T*const* arr, const T& obj, int currSize) const throw(AirLineException);
};



template<typename T>
int Airline::getIndex(T*const* arr, const T& obj, int currSize) const 
throw(AirLineException)
{
	for (int i = 0; i < currSize; i++)
	{
		//check if implementation belongs here!, operator=
		if (*arr[i] == obj)
		{
			return i;
		}
	}
	
	char msg[150];
	strcpy(msg, "The object of type - ");
	strcat(msg, typeid(obj).name() + 6);
	strcat(msg, " is not in this airline # ");
	
	throw AirLineException(msg);
	return -1;  
}


#endif