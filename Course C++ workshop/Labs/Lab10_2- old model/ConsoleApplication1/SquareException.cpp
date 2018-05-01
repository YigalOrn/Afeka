#include <iostream>
using namespace std;


#include "SquareException.h"


SquareException::SquareException(int thickness, int width)
	: ShapeException(thickness), width(width)
{
}

void SquareException::toOs(ostream& os) const
{
	os << "The value of width - " << width << " is incorrect!" << endl;
}











