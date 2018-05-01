#ifndef __Square_h
#define __Square_h

#include <iostream>

class Square :public Shape
{


public:

	//no default c'tor as in lab 10_1
	Square(const char* color, int thickness, int width);

	Square(iostream& is);

	void show() const;

	float getArea() const;

	float getPerimeter() const;

	void draw() const;

	Shape* clone() const;

	virtual void toOs(ostream& os) const;

	void setWidth(int);

	const int& getWidth() const;

private:

	int width;

};

#endif//__Square_h