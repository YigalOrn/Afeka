#ifndef __SEAT_H_
#define __SEAT_H_

#include <iostream>
#include <string>
using namespace std;

class Seat
{
public:
	enum SeatType { TAKEN, FREE };
	Seat(double price = 100, SeatType st = SeatType::FREE);

	void setPrice(double price) throw (const string&);
	void setSeat(SeatType st) throw (const string&);
	double getPrice() const;
	const string& getSeatTypeAsString() const;

	friend ostream& operator<<(ostream& os, const Seat& s);

private:
	
	static const string seatTypes[];
	
	double price;
	SeatType seatType;
};
#endif

