#include "Ticket.h"

Ticket::Ticket(const Flight& f, const Seat& s, const Date& d) : flight(f), seat(s), flightDate(d) {}

Ticket::Ticket(const Ticket& t) : flight(t.getFlight()), seat(t.getSeat()), flightDate(t.getTicketDate()) {}

double Ticket::getTicketCost() const
{
	return seat.getPrice();
}

ostream& operator<<(ostream& os, const Ticket& t)
{
	os << "Flight destination: " << t.getFlight().getDestination() << endl;
	os << "Flight date: " << t.getTicketDate() << endl;
	os << "Seat: " << t.getSeat() << endl;
	return os;
}

bool Ticket::operator==(const Ticket& t) const
{
	return flight == t.getFlight() && flightDate == t.getTicketDate();
}

const Flight& Ticket::getFlight() const
{
	return flight;
}

const Seat& Ticket::getSeat() const
{
	return seat;
}

const Date& Ticket::getTicketDate() const
{
	return flightDate;
}