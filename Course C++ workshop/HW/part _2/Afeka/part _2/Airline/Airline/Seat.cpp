#include <ostream>
#include <string>
using namespace std;

#include "Seat.h"

Seat::Seat(double price = 100, SeatType st = SeatType::FREE) : price(price), seatType(st) {}

void Seat::setPrice(double price)
{
	if (price > 0)
	{
		this->price = price;
	}
	else
	{
		// throw exc
	}
}

void Seat::setSeat(SeatType st)
{
	if (st)
	{
		seatType = st;
	}
	else
	{
		// throw exc
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
	return os << "Dont forget to impl.  operator<< in Seat" << endl;
}