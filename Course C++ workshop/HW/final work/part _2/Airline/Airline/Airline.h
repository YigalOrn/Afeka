#ifndef __AIRLINE_H
#define __AIRLINE_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

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
#include "List.h";
#include "Iterator.h"

class Airline
{
	string airlineName;

	vector<Flight> flightsVec;
	int maxNumberOfFlights;

	//chosen array
	List<Plane> planesList;
	int maxNumberOfPlanes;
	int numberOfPlanes;

	vector<Customer> customersVec;
	int maxNumberOfCustomers;
	
	vector<AirCrew*> crewVec;
	int maxNumberOfCrewMembers;
	
	vector<Order> ordersVec;
	int maxNumberOfOrders;
	
public:
	Airline(
		const string name, 
		int maxNumberOfFlights = 550, 
		int maxNumberOfPlanes = 20, 
		int maxNumberOfCustomers = 200,
		int maxNumberOfCrewMembers = 30, 
		int maxNumberOfOrders = 300
		);

	~Airline();

	void setName(const string name) throw(AirLineException);

	void addFlight(const Flight& f) throw(AirLineException, const string&);
	void addPlane(const Plane& p) throw(AirLineException);
	void addCustomer(const Customer& c) throw(AirLineException);
	void addCrewMember(const AirCrew& ac) throw(AirLineException);
	int addOrder(const Date& date, const Customer& cust) 
		throw(AirLineException);

	Order* getOrder(int orderId);

	friend ostream& operator<<(ostream& out, const Airline& a);

	const string& getAirlineName() const { return airlineName;  }

	const vector<Flight>& getFlights() const;
	int getFlightsAmount() const;

	const List<Plane>& Airline::getPlanes() const;
	int getPlanesAmount() const;

	const vector<Customer>& getCustomers() const;
	int getCustomersAmount() const;

	const vector<AirCrew*>& getAirCrews() const;
	int getAirCrewsAmount() const;

	const vector<Order>& getOrders() const;
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
	Array<Flight>* getWantedFlights(const string& destToSearch, const Date& dateToSearch) const throw(AirLineException);

private:
	Airline(const Airline& other);
	const Airline& operator=(const Airline& other);
};

#endif//__AIRLINE_H