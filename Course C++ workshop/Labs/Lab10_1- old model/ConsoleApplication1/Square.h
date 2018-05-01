#ifndef __Square_h
#define __Square_h

class Square :public Shape
{
public:

	Square(const char* color = 0, int thickness = 0, int width = 0);

	void show() const;

	float getArea() const;

	float getPerimeter() const;

	void draw() const;

	Shape* clone() const;

	virtual void toOs(iostream& os) const;

	virtual void toIs(iostream& is);

	void setWidth(int);

	const int& getWidth() const;

private:

	int width;

};

#endif//__Square_h