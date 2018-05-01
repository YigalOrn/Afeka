#include <ostream>
#include <string>
using namespace std;

#include "Seat.h"

Seat::Seat(double price, SeatType st) : price(price), seatType(st) {}

void Seat::setPrice(double price) throw (const char*)
{
	if (price > 0)
	{
		this->price = price;
	}
	else
	{
		throw "# Price cannot be negative #";
	}
}

void Seat::setSeat(SeatType st) throw (const char*)
{
	if (st)
	{
		seatType = st;
	}
	else
	{
		throw "# Seat provided is NULL #";
	}
}

double Seat::getPrice() const
{
	return price;
}

const char* Seat::getSeatTypeAsString() const
{
	return seatTypes[seatType];
}

ostream& operator<<(ostream& os, const Seat& s)
{
	os << "Seat price: " << s.getPrice() << " , " << s.getSeatTypeAsString() << endl;
	return os;
}

const char* const Seat::seatTypes[] = { "Taken", "Free" };

