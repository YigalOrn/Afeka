#include <ostream>
#include <string>
using namespace std;

#include "Plane.h"

Plane::Plane(int maxNumOfSeats) : maxNumOfSeats(maxNumOfSeats)
{
	planeId = planeIdCounter++;
}

const int Plane::getMaxNumOfSeats() const
{
	return maxNumOfSeats;
}

ostream& operator<<(ostream& os, const Plane& p)
{
	os << "Plane ID: " << p.getPlaneId() << endl;
	os << "Plane has: " << p.getMaxNumOfSeats() << " seats";
	return os;
}

bool Plane::operator==(const Plane& plane) const
{
	return this->getPlaneId() == plane.getPlaneId();
}

int Plane::planeIdCounter = 1;