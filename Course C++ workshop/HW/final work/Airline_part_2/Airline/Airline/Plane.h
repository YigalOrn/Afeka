#ifndef __PLANE_H_
#define __PLANE_H_

#include "Seat.h"
#include <ostream>
using namespace std;

class Plane
{
	static int planeIdCounter;
	int planeId;

	int maxNumOfSeats;

public:
	Plane(int maxNumOfSeats = 100);

	const int getMaxNumOfSeats() const;
	int getPlaneId() const { return planeId; }

	bool operator==(const Plane& plane) const;

	friend ostream& operator<<(ostream& os, const Plane& p);
};
#endif