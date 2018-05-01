#ifndef __SEAT_H_
#define __SEAT_H_

#include <ostream>
using namespace std;

// Write this in the CPP file
// const char* seatTypes[] = {"Taken", "Free"}; 

class Seat
{
	enum SeatType {TAKEN, FREE}; 

	double price;
	SeatType seatType;
public:
	Seat(double price, SeatType st=FREE);

	void setPrice(double price);
	void setSeat(SeatType st);

	double getPrice() const;
	const char* getSeatTypeAsString() const;

	friend ostream& operator<<(ostream& out, const Seat& s);
};
#endif