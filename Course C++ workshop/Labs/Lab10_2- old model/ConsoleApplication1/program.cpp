

#include <iostream>
#include <typeinfo>
#include <fstream>
using namespace std;


#include "Shape.h"
#include "Square.h"
#include "Circle.h"

#include "ShapeException.h"
#include "CircleException.h"
#include "SquareException.h"


int main(void)
{

	//prototypes
	void saveShapes();
	void loadShapes();

	saveShapes();
	loadShapes();

	return 0;
}//main

void saveShapes()
{
	//prototypes
	void readShapes(Shape**&, int);
	void saveToTextFile(Shape**&, int);
	void freeShapesArr(Shape**&, int);

	int numOfShapes = 0;

	cout << "Enter how many shapes: " << endl;
	cin >> numOfShapes;

	Shape** shapesArr = new Shape*[numOfShapes];

	//init shapes array
	readShapes(shapesArr, numOfShapes);

	//write shapes to text file
	saveToTextFile(shapesArr, numOfShapes);

	//free allocated memory
	freeShapesArr(shapesArr, numOfShapes);

}//saveShapes

void readShapes(Shape**& shapesArr, int size)
{
	int choice = -1;
	static const int len = 20;
	static char color[len];
	static int thickness;

	for (int i = 0; i < size; i++)
	{
		cout << "What shape would you like to create (0-Circle, 1-Square) ? " << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:
		{
			float radius;

			cout << "# Circle #" << endl;
			cout << "Enter color: " << endl;
			cin.ignore();
			cin.getline(color, len);
			cout << "Enter thickness, radius: " << endl;
			cin >> thickness >> radius;
			shapesArr[i] = new Circle(color, thickness, radius);

			break;
		}
		case 1:
		{
			int width;

			cout << "# Square #" << endl;
			cout << "Enter color: " << endl;
			cin.ignore();
			cin.getline(color, len);
			cout << "Enter thickness, width: " << endl;
			cin >> thickness >> width;
			shapesArr[i] = new Square(color, thickness, width);

			break;
		}
		default:
		{
			cout << "# No such choice, try again #" << endl;
			i--;
			break;
		}

		}//switch
	}//for
}

void saveToTextFile(Shape**& shapesArr, int size)
{

	fstream fst;
	fst.open("shapes.txt", ios::out|ios::trunc);


	//if (!fst) {/*checks if file stream objects is open*/}


	fst << size << endl;

	for (size_t i = 0; i < size; i++)
	{

		//save shape type using special independent method
		shapesArr[i]->saveShapeClassToFile(fst);

		//save shape info
		fst << (*shapesArr[i]) << endl;

	}//for


	fst.close();

}

void loadShapes()
{

	//prototypes
	void showShapesAfterLoadingFromFile(Shape**, int);
	void freeShapesArr(Shape**&, int);

	//file object
	fstream fst;
	fst.open("shapes.txt", ios::in);

	int numOfShapes;
	const int len = 20;
	char type[len];

	fst >> numOfShapes;

	//create shapes pointer-array
	Shape** shapesArr = new Shape*[numOfShapes];

	//load each shape
	for (int i = 0; i < numOfShapes; i++)
	{

		//nedd to write and read the len of the type!!, also change in Shape.cpp!!
		fst >> type;

		if (strcmp(type, "Circle") == 0)
		{
			shapesArr[i] = new Circle(fst);
		}
		else if (strcmp(type, "Square") == 0)
		{
			shapesArr[i] = new Square(fst);
		}

	}//for


	fst.close();

	//show shapes after loading
	showShapesAfterLoadingFromFile(shapesArr, numOfShapes);

	//free allocated memory
	freeShapesArr(shapesArr, numOfShapes);

}//loadShapes

void showShapesAfterLoadingFromFile(Shape** shapesArr, int size)
{
	cout << "\n------------------------------------------------------\n" << endl;

	for (int i = 0; i < size; i++)
	{
		shapesArr[i]->show();
	}//for
}

void freeShapesArr(Shape**& shapesArr, int size)
{
	for (int i = 0; i < size; i++)
	{
		delete shapesArr[i];
	}
	delete[]shapesArr;
}//




