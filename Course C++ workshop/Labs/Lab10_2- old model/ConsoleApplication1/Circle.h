#ifndef __Circle_h
#define __Circle_h

#include <iostream>

class Circle :public Shape
{


public:

	//no default c'tor as in lab 10_1
	Circle(const char* color, int thickness, float radius);

	Circle(iostream& is);

	void show() const;

	float getArea() const;

	float getPerimeter() const;

	Shape* clone()const;

	virtual void toOs(iostream& os) const;

	void setRadius(float radius);

	const float& getRadius() const;

private:

	float radius;

};


#endif//__Circle_h




