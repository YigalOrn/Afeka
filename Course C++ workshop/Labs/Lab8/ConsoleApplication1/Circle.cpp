/*
http://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c
*/

#include <iostream>
using namespace std;

#include <typeinfo>

#define _USE_MATH_DEFINES
#include<math.h>//doesnt work with cmath...


#include "Shape.h"
#include "Circle.h"


Circle::Circle(const char* color, int thickness, float radius) :Shape(color, thickness)
{
	setRadius(radius);
}

void Circle::show() const
{
	cout << (typeid(*this).name() + 6) << " details: color- " << getColor() << ", thickness- " << getThickness() << ", radius- " << getRadius() << ", perimeter-" << getPerimeter() << ", area- " << getArea() << endl;
}

Shape* Circle::clone()const
{
	return (new Circle(*this));
}

float Circle::getArea() const
{
	return(M_PI*(pow(getRadius(), 2)));
}

float Circle::getPerimeter() const
{
	return (2 * M_PI*getRadius());
}

void Circle::setRadius(float radius)
{
	this->radius = radius;
}

const float& Circle::getRadius() const
{
	return radius;
}