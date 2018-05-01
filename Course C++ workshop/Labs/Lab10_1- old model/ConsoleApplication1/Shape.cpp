
#include <iostream>
#include <cstring>
#include <typeinfo>
using namespace std;


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
		//throw ShapeException(th);
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


iostream& operator<<(iostream& os, const Shape& shape)
{
	if (typeid(os) == typeid(fstream))
	{
		os << typeid(shape).name() << "\n";
		os << strlen(shape.color) << " " << shape.color << "\n";
		os << shape.thickness << "\n";
		shape.toOs(os);
	}
	else
	{
		shape.show();
	}
	return os;
}

iostream& operator>>(iostream& is, Shape& shape)
{
	if (typeid(is) == typeid(fstream))
	{
		int len = strlen(typeid(shape).name());
		char* buf = new char[len + 1];
		char delimeter;

		is >> buf;
		is >> buf;
		is >> len;
		char* str = new char[len+1];
		is >> str;
		shape.setColor(str);
		is >> shape.thickness;

		shape.toIs(is);

		delete[]buf;
		delete[]str;
	}
	else
	{
		//implement...
	}
	return is;
}











