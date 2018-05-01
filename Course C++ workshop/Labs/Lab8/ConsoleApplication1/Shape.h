#ifndef __Shape_h
#define __Shape_h


class Shape
{

public:

	//client interface
	virtual void show() const = 0;

	virtual float getArea() const = 0;

	virtual float getPerimeter() const = 0;

	virtual Shape* clone() const = 0;


	//class Shape is abstract...
protected:

	Shape(const char* color, int thickness);

	Shape(const Shape&);

	virtual ~Shape(void);

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