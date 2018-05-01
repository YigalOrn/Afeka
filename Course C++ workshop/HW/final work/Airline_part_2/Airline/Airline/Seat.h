#ifndef __SEAT_H_
#define __SEAT_H_

#include <ostream>
using namespace std;

// Write this in the CPP file
// const char* seatTypes[] = {"Taken", "Free"}; 

class Seat
{
	static const char* const seatTypes[];
	enum SeatType {TAKEN, FREE}; 

	double price;
	SeatType seatType;
public:
	Seat(double price = 100, SeatType st = SeatType::FREE);

	void setPrice(double price) throw (const char*);
	void setSeat(SeatType st) throw (const char*);
	double getPrice() const;
	const char* getSeatTypeAsString() const;

	friend ostream& operator<<(ostream& os, const Seat& s);
};
#endif

