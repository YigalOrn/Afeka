#ifndef __Circle_h
#define __Circle_h


class Circle :public Shape
{


public:

	Circle(const char* color, int thickness, float radius);

	void show() const;

	float getArea() const;

	float getPerimeter() const;

	Shape* clone()const;

	void setRadius(float radius);

	const float& getRadius() const;

private:

	float radius;


};

#endif//__Circle_h