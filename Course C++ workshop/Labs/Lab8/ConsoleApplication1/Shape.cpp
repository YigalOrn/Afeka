
#include <cstring>
#include <iostream>
using namespace std;

#include <typeinfo>

#include "Shape.h"


Shape::Shape(const char* color, int thickness) : color(0)
{
	setColor(color);
	setThickness(thickness);
}

Shape::Shape(const Shape& other) :color(0)
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

void Shape::setThickness(int th)
{
	this->thickness = th;
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