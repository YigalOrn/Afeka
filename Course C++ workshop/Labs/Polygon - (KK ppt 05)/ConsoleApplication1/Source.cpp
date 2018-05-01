#include <iostream>
using namespace std;

class Point
{

	int x, y;
	int index;

public:
	Point(int x = 0, int y = 0) :x(x), y(y)
	{
		cout << "In Point::Point";
		show();
		cout << endl;
	}

	~Point()
	{
		cout << "In Point::~Point :: Index - " << index << endl;
	}

	void show() const
	{
		cout << "(" << x << ", " << y << ") ";
	}

	void setIndex(int i)
	{
		index = i;
	}
};

class Polygon
{
	int numOfPoints;
	Point* points;
public:
	Polygon(int numOfPoints) : numOfPoints(numOfPoints)
	{
		points = new Point[numOfPoints];
	}

	Polygon(const Polygon& other) : numOfPoints(other.numOfPoints)
	{
		points = new Point[numOfPoints];
		for (int i = 0; i < numOfPoints; i++)
		{
			points[i] = other.points[i];
		}//for
	}

	~Polygon()
	{
		cout << "In Polygon::~Polygon" << endl;
		delete[]points;
	}

	void setPoint(int index, const Point& p)
	{
		points[index] = p;
		points[index].setIndex(index);
	}

	void show() const
	{
		cout << "The polygon has : " << numOfPoints << " points" << endl;
		cout << "The points are:" << endl;
		for (int i = 0; i < numOfPoints; i++)
		{
			points[i].show();
		}//for
		cout << endl;
	}

};

int main(void)
{
	Polygon triangle(3);

	triangle.setPoint(0, Point{ 1, 1 });
	triangle.setPoint(1, Point{ 0, 10 });
	triangle.setPoint(2, Point{ 6, 7 });

	return 0;
}//main



