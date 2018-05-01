
#include <iostream>
#include <iomanip>
#include <cstring>
#include <typeinfo>
using namespace std;


#include "ShapeException.h"
#include "Shape.h"
#include "Circle.h"
#include "Square.h"


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

Shape::Shape(iostream& is) : color(0)
{

	int len;
	is.read((char*)&len, sizeof(len));


	//cout << "DEBUG: Shape file c'tor - len " << len << endl;//DEBUG

	char* str = new char[len + 1];
	is.read((char*)str, (sizeof(char)*len));
	str[len] = '\0';


	//cout << "DEBUG: Shape file c'tor - str " << str << endl;//DEBUG

	//has delete[]
	setColor(str);

	//already checked
	is.read((char*)&thickness, sizeof(thickness));


	//cout << "DEBUG: Shape file c'tor - thickness " << thickness << endl;//DEBUG

	delete[]str;
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


ostream& operator<<(ostream& os, const Shape& shape)
{
	if (typeid(os) == typeid(fstream))
	{
		int len = strlen(shape.color);
		char* str = new char[len + 1];
		str = _strdup(shape.getColor());

		//cout << "DEBUG: Shape operator << - len " << len << endl;//DEBUG
		//cout << "DEBUG: Shape operator << - str " << str << endl;//DEBUG

		os.write((const char*)&len, sizeof(len));
		os.write((const char*)str, (sizeof(char)*len));
		
		//cout << "DEBUG: Shape operator << - thickness " << shape.thickness << endl;//DEBUG

		os.write((const char*)&shape.thickness, sizeof(shape.thickness));

		shape.toOs(os);

		delete[]str;
	}
	else
	{
		shape.show();
	}
	return os;
}

void Shape::saveShapeClassToFile(iostream& os)
{
	int len = strlen(typeid(*this).name() + 6);
	char *str = new char[len + 1];
	str = _strdup(typeid(*this).name() + 6);

	//cout << "DEBUG: Shape type to file - len " << len << endl;//DEBUG
	//cout << "DEBUG: Shape type to file - str " << str << endl;//DEBUG

	//cout << "DEBUG: Shape type to file - sizeof(len) " << sizeof(len) << endl;//DEBUG
	//cout << "DEBUG: Shape type to file - (sizeof(char)*len) " << (sizeof(char)*len) << endl;//DEBUG


	os.write((const char*)&len, sizeof(len));
	os.write((const char*)str, (sizeof(char)*len));

	delete[]str;
}










