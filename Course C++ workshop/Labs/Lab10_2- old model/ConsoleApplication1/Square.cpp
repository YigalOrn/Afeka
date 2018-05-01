

#include <iostream>
using namespace std;

#include <typeinfo>
#include<cmath>


#include "SquareException.h"
#include "Shape.h"
#include "Square.h"


Square::Square(const char* color, int thickness, int width) throw (SquareException) :Shape(color, thickness)
{
	setWidth(width);
}

Square::Square(iostream& is): Shape(is)
{
	is >> width;
}

void Square::show() const
{
	cout << (typeid(*this).name() + 6) << " details: color- " << getColor() << ", thickness- " << getThickness() << ", width- " << getWidth() << ", perimeter- " << getPerimeter() << ", area- " << getArea() << endl;
}

float Square::getArea() const
{
	return (pow(getWidth(), 2));
}

float Square::getPerimeter() const
{
	return (getWidth() * 4);
}

void Square::draw() const
{
	int t = getWidth() + (2 * getThickness());
	int k = getThickness();
	int m = getThickness();
	int ctr = 0;

	for (int i = 0; i < t; i++)
	{
		for (int j = 0; j < t; j++)
		{
			if (i == k && j == m)
			{
				while (ctr < getWidth())
				{
					cout << ' ';
					ctr++;
				}
				ctr = 0;
				k = (k + 1) % (getWidth() + getThickness());
				j += getWidth();
			}
			cout << 'C';
		}//for_j
		cout << endl;
	}//for_i
}

Shape* Square::clone() const
{
	return(new Square(*this));
}

void Square::toOs(iostream& os) const
{
	os << width;
}

void Square::setWidth(int width) throw (SquareException)
{
	if (width < 0)
	{
		//throw SquareException(getThickness(), width);
	}
	else
	{
		this->width = width;
	}
}

const int& Square::getWidth() const
{
	return width;
}

