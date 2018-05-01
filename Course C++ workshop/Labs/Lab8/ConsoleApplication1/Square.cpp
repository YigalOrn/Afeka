

#include <iostream>
using namespace std;

#include <typeinfo>
#include<cmath>


#include "Shape.h"
#include "Square.h"


Square::Square(const char* color, int thickness, int width) :Shape(color, thickness)
{
	setWidth(width);
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
	int width = getWidth();
	int thickness = getThickness();

	int t = width + (2 * thickness);
	int m = thickness;
	int k = m;
	int ctr = 0;

	for (register int i = 0; i < t; i++)
	{
		for (register int j = 0; j < t; j++)
		{
			if (i == k && j == m)
			{
				while (ctr < width)
				{
					cout << ' ';
					ctr++;
				}
				ctr = 0;
				k = (k + 1) % (width + thickness);
				j += width;
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

void Square::setWidth(int width)
{
	this->width = width;
}

const int& Square::getWidth() const
{
	return width;
}

