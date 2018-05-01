#include <iostream>
using namespace std;

class Shapeable
{
public:
	virtual void draw()const =0;
};

class Shape : public Shapeable
{
	int numOfPoints;
	string name;

public:
	Shape(int numOfPoints, const string& name) : numOfPoints(numOfPoints), name(name) {}

	virtual void draw() const =0
	{
		cout << "The shape is " << name.c_str() << ", numOfPoints=" << numOfPoints;
	}
};

class Circle : public Shape
{
	int radius;

public:
	Circle(int numOfPoints, const string& name, int radius) : Shape(numOfPoints, name), radius(radius) {}

	virtual void draw() const
	{
		Shape::draw();
		cout << ", radius=" << radius;
	}
};

class ShapeProperty : public Shapeable
{
	Shapeable* theShape;
public:
	ShapeProperty(Shapeable* theShape) : theShape(theShape) {}

	virtual void draw() const 
	{
		theShape->draw();
	}
};

class ShapeWithBorder : public ShapeProperty
{
	
	int borderLength;
public:
	ShapeWithBorder(Shapeable* theShape, int borderLength) : ShapeProperty(theShape), borderLength(borderLength) {}
	virtual void draw() const
	{
		ShapeProperty::draw();
		cout << ", border=" << borderLength;
	}
};

class ShapeWithColor : public ShapeProperty
{
	string color;
public:
	ShapeWithColor(Shapeable* theShape, const string& color) : ShapeProperty(theShape), color(color) {}
	virtual void draw() const
	{
		ShapeProperty::draw();
		cout << ", color=" << color.c_str();
	}
};

void main()
{
	Shapeable* s1 = new Circle(0, "circle", 5);
	s1->draw();
	cout << endl;

	Shapeable* s2 = new ShapeWithBorder(
		new ShapeWithColor(
		new Circle(0, "circle", 5), "red"), 2);
	s2->draw();
	cout << endl;
}