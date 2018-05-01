#include "Seat.h"

Seat::Seat(double price, SeatType st) : price(price), seatType(st) {}

void Seat::setPrice(double price) throw (const string&)
{
	if (price > 0)
	{
		this->price = price;
	}
	else
	{
		throw string("# Price cannot be negative #");
	}
}

void Seat::setSeat(SeatType st) throw (const string&)
{
	seatType = st;
}

double Seat::getPrice() const
{
	return price;
}

const string& Seat::getSeatTypeAsString() const
{
	return seatTypes[seatType];
}

ostream& operator<<(ostream& os, const Seat& s)
{
	os << "Seat price: " << s.getPrice() << " , " << s.getSeatTypeAsString() << endl;
	return os;
}

const string Seat::seatTypes[] = { string("Taken"), string("Free") };

