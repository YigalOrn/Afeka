#ifndef __Circle_h
#define __Circle_h


class Circle :public Shape
{


public:

	Circle(const char* color = 0, int thickness = 0, float radius = 0);

	void show() const;

	float getArea() const;

	float getPerimeter() const;

	Shape* clone()const;

	virtual void toOs(iostream& os) const;

	virtual void toIs(iostream& is);

	void setRadius(float radius);

	const float& getRadius() const;

private:

	float radius;


};

#endif//__Circle_h