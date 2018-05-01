#include <ostream>
#include <string>
using namespace std;

#include "Plane.h"

Plane::Plane(int maxNumOfSeats = 100) : maxNumOfSeats(maxNumOfSeats){}

const int Plane::getMaxNumOfSeats() const
{
	return maxNumOfSeats;
}

ostream& operator<<(ostream& os, const Plane& p)
{
	return os << "Dont forget to impl.  operator<< in PLANE" << endl;
}