//#define NDEBUG//in use with assert macro

#include <iostream>
using namespace std;

#include <cassert>
#include <typeinfo>

#include "Shape.h"
#include "Square.h"
#include "Circle.h"


int main(void)
{
	//prototypes
	void initShapesArray(Shape**, int size);
	void showShapes(Shape** shapesArray, int size);

	Shape **shapes = 0;
	int size = 0;

	cout << "How many shapes will there be ? " << endl;
	cin >> size;

	shapes = new Shape*[size];
	//exchange with try-catch clause
	//assert(shapes != 0);
	if (shapes == 0)
	{
		cout << "# Allocation failed #" << endl;
		system("PAUSE");
		exit(1);
	}

	initShapesArray(shapes, size);

	//show shapes
	showShapes(shapes, size);


	Shape **clonedShapes = new Shape*[size];
	//exchange with try-catch clause
	assert(clonedShapes != 0);

	for (int i = 0; i < size; i++)
	{
		clonedShapes[i] = shapes[i]->clone();
		//debuger shows different addresses :)
	
		//if we wanted to use the assignment operator --> .opertor=(...) we would have to use virtual methods and overriding! not overloading!!!! were each derived class calls its direct father  assignment operator method using the binary scope resolution! i.e base::methodName(...) 
	}

	//show cloned shapes
	showShapes(clonedShapes, size);


	return 0;
}//main

void initShapesArray(Shape** shapesArray, int size)
{
	//prototypes
	Shape* helpCreateShape(int choice);

	int choice;

	for (int i = 0; i < size; i++)
	{
		
		cin.ignore();

		cout << "Are you a Square ? (1-yes, 2-no)" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			shapesArray[i] = helpCreateShape(1);
			break;
		}
		case 2:
		{
			shapesArray[i] = helpCreateShape(2);
			break;
		}
		default:
		{
			cout << "# Your input is incorrect, try again... #" << endl;
			i--;
			break;
		}

		}//switch

	}//for_i


}//initShapesArray

Shape* helpCreateShape(int choice)
{
	char color[20];
	int thickness;

	float radius;
	int width;


	cin.ignore();

	cout << "Enter shape color(<19): " << endl;
	cin.getline(color, 20);

	cin.ignore();


	cout << "Enter thickness: " << endl;
	cin >> thickness;



	switch (choice)
	{
	case 1:
	{
		int width;

		cin.ignore();

		cout << "Enter width: " << endl;
		cin >> width;

		return (new Square(color, thickness, width));

		break;
	}
	case 2:
	{
		int radius;

		cin.ignore();

		cout << "Enter radius: " << endl;
		cin >> radius;

		return (new Circle(color, thickness, radius));

		break;
	}

	}//switch


}//helpCreateShape

void showShapes(Shape** shapes, int size)
{

	//show shapes
	cout << "\n\n\n# ----- shapes ----- #" << endl;
	for (int i = 0; i < size; i++)
	{
		shapes[i]->show();

		if (typeid(*shapes[i]) == typeid(Square))
		{
			Square *sqaurechik = dynamic_cast<Square*>(shapes[i]);
			sqaurechik->draw();
		}

	}
	cout << "# ----- shapes ----- #\n\n\n" << endl;

}










