#ifndef __Square_h
#define __Square_h

class Square :public Shape
{
public:

	Square(const char* color, int thickness, int width);

	void show() const;

	float getArea() const;

	float getPerimeter() const;

	void draw() const;

	Shape* clone() const;

	void setWidth(int);

	const int& getWidth() const;

private:

	int width;

};

#endif//__Square_h