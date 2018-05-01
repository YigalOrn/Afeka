#include <iostream>
using namespace std;



#include "CircleException.h"


CircleException::CircleException(int thickness, float radius)
	: ShapeException(thickness), radius(radius)
{
}

void CircleException::toOs(ostream& os) const
{
	os << "The value of radius - " << radius << " is incorrect!" << endl;
}

