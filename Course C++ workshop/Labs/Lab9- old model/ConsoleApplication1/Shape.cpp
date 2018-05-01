
#include <cstring>
#include <iostream>
using namespace std;

#include <typeinfo>

#include "ShapeException.h"
#include "Shape.h"


Shape::Shape(const char* color, int thickness) throw(ShapeException) : color(0)
{
	setThickness(thickness);
	
	//if thrown no memory has been allocated
	setColor(color);
}

Shape::Shape(const Shape& other) throw() :color(0)
{
	setColor(other.getColor());
	setThickness(other.getThickness());
}

Shape:: ~Shape()
{
	delete[] color;
	color = 0;
}

//abstract defualt
void Shape::show() const
{
	//cout << "Shape details: color- " << getColor() << ", thickness- " << getThickness() << endl;
	cout << (typeid(*this).name() + 6) << " details: color- " << getColor() << ", thickness- " << getThickness() << endl;
}

//seters
void Shape::setColor(const char* strColor)
{
	delete[] this->color;
	color = _strdup(strColor);
}

void Shape::setThickness(int th) throw(ShapeException)
{
	if (th < 1)
	{
		throw ShapeException(th);
	}
	else
	{
		this->thickness = th;
	}
}

//geters
const char* Shape::getColor() const
{
	return this->color;
}

const int& Shape::getThickness()const
{
	return thickness;
}