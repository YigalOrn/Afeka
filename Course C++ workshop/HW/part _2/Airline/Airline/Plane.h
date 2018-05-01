#ifndef __PLANE_H_
#define __PLANE_H_

#include "Seat.h"
#include <ostream>
using namespace std;

class Plane
{
	int maxNumOfSeats;

public:
	Plane(int maxNumOfSeats = 100);

	int getMaxNumOfSeats() const;

	friend ostream& operator<<(ostream& out, const Plane& p);
};
#endif