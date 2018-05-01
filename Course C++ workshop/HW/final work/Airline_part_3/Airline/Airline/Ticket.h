#ifndef __TICKET_H_
#define __TICKET_H_

#include <iostream>
using namespace std;

#include "Flight.h"
#include "Seat.h"


class Ticket
{
	const Flight& flight; 
	const Seat& seat;
	const Date flightDate;

public: 
	Ticket(const Flight& f, const Seat& s, const Date& d);
	Ticket(const Ticket& t);

	double getTicketCost() const;

	friend ostream& operator<<(ostream& os, const Ticket& t);

	bool operator==(const Ticket& t) const;

	const Flight& getFlight() const;
	const Seat& getSeat() const;
	const Date& getTicketDate() const;

private:
	const Ticket& operator=(const Ticket& t);
};
#endif