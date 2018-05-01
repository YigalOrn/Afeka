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

#include <ostream>
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
		int maxNumberOfCrewMembers = 30, int maxNumberOfOrders = 300);

	~Airline();

	void setName(const char* name);

	bool addFlight(Flight& f);
	bool addPlane(Plane& p);
	bool addCustomer(Customer& c);
	bool addCrewMember(AirCrew& ac);
	bool addOrder(Order& o);

	friend ostream& operator<<(ostream& out, const Airline& a);


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


	bool addStaffMemberToFlight(AirCrew& ac, Flight& f);
	bool removeStaffMemberFromFlight(const AirCrew& ac, const Flight& f);

	Ticket createTicketForFlight(const Flight& f) const;
	bool cancelOrder(const Order& o);

private:
	Airline(const Airline& other);
	const Airline& operator=(const Airline& other);
	void initNumberFields();
};
#endif