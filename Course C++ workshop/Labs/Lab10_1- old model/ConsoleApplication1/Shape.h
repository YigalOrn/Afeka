#ifndef __Shape_h
#define __Shape_h


class Shape
{


	friend iostream& operator<<(iostream& os, const Shape& shape);
	friend iostream& operator>>(iostream& os, Shape& shape);

public:

	virtual ~Shape();

	//client interface
	virtual void show() const = 0;

	virtual float getArea() const = 0;

	virtual float getPerimeter() const = 0;

	virtual Shape* clone() const = 0;

	virtual void toOs(iostream& os) const = 0;
	
	virtual void toIs(iostream& is) = 0;

	//class Shape is abstract...
protected:

	Shape(const char* color, int thickness);
	Shape(const Shape&);


	//seters
	void setColor(const char*);

	void setThickness(int);

	//geters
	const char* getColor() const;

	const int& getThickness() const;



private:

	int thickness;

	char* color;

};

#endif//__Shape_h