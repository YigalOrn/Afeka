#ifndef __TICKET_H_
#define __TICKET_H_

#include "Flight.h"
#include "Seat.h"
#include <ostream>
using namespace std;

class Ticket
{
	const Flight& flight; 
	const Seat& seat;
	const Date flightDate;

public: 
	Ticket(const Flight& f, const Seat& s, const Date& d);
	~Ticket();

	double getTicketCost() const;

	friend ostream& operator<<(ostream& out, const Ticket& t);

	bool operator==(const Ticket& t) const;

	const Flight& getFlight() const;
	const Seat& getSeat() const;
	const Date& getTicketDate() const;

private:
	Ticket(const Ticket& t);
	const Ticket& operator=(const Ticket& t);

};
#endif