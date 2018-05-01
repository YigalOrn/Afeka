#include <iostream>
using namespace std;

#include "ShapeException.h"


ShapeException::ShapeException(int thickness) :thickness(thickness)
{
}

ostream& operator<<(ostream& os, const ShapeException & shapeException)
{
	shapeException.toOs(os);
	return os;
}

void ShapeException::toOs(ostream& os) const
{
	os << "The value of thickness - " << thickness << " is incorrect!" << endl;
}