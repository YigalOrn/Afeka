

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
	void readCircles(Shape**&, int, int);
	void readSquares(Shape**&, int, int);
	void saveToTextFile(Shape**&, int, int);

	int numOfCircles = 0;
	int numOfSquares = 0;

	cout << "Enter how many circles: " << endl;
	cin >> numOfCircles;

	cout << "Enter how many squares: " << endl;
	cin >> numOfSquares;

	Shape** shapesArr = new Shape*[numOfCircles + numOfSquares];


	//init shapes array
	readCircles(shapesArr, 0, numOfCircles);
	readSquares(shapesArr, numOfCircles, numOfSquares + numOfCircles);

	//write shapes to text file
	saveToTextFile(shapesArr, numOfSquares, numOfCircles);


	//free allocated memory
	for (int i = 0; i < (numOfCircles + numOfSquares); i++)
	{
		delete shapesArr[i];
	}
	delete[]shapesArr;



}//saveShapes

void readCircles(Shape**& arr, int a, int b)
{
	char color[20];
	int thickness;
	float radius;

	for (int i = a; i < b; i++)
	{
		cout << "# Circle #" << endl;
		cout << "Enter color: " << endl;
		cin.ignore();
		cin.getline(color, 20);
		//cin.ignore();
		cout << "Enter thickness, radius: " << endl;
		cin >> thickness >> radius;
		arr[i] = new Circle(color, thickness, radius);
	}//for
}

void readSquares(Shape**& arr, int a, int b)
{
	char color[20];
	int thickness;
	int width;

	for (int i = a; i < b; i++)
	{
		cout << "# Square #" << endl;
		cout << "Enter color: " << endl;
		cin.ignore();
		cin.getline(color, 20);
		//cin.ignore();
		cout << "Enter thickness, width: " << endl;
		cin >> thickness >> width;
		arr[i] = new Square(color, thickness, width);
	}//for
}

void saveToTextFile(Shape**& arr, int squares, int circles)
{

	fstream fst;

	fst.open("shapes.txt", ios::out, ios::trunc);

	fst << (squares + circles) << "\n";
	fst << circles << "\n";

	//generic?
	for (int i = 0; i < circles; i++)
	{
		fst << (*arr[i])<<"\n";
	}//for

	fst << squares << "\n";

	for (int i = circles; i < (circles + squares); i++)
	{
		fst << (*arr[i])<< "\n";
	}//for

	fst.close();

}

void loadShapes()
{


	//prototypes
	void showShapesAfterLoadingFromFile(Shape**, int);

	//file object
	fstream fst;

	fst.open("shapes.txt", ios::in);

	int totSize;
	int circles;
	int squares;


	fst >> totSize;
	fst >> circles;

	Shape** shapesArr = new Shape*[totSize];


	//load circles
	for (int i = 0; i < circles; i++)
	{
		//instead of using a default c'tor could use a c'tor that accepts a file object ref.. 
		shapesArr[i] = new Circle();
		fst >> (*shapesArr[i]);
	}//for

	fst >> squares;

	//load squares
	for (int i = circles; i < totSize; i++)
	{
		shapesArr[i] = new Square();
		fst >> (*shapesArr[i]);
	}//for

	fst.close();


	showShapesAfterLoadingFromFile(shapesArr, totSize);


}//loadShapes

void showShapesAfterLoadingFromFile(Shape** shapesArr, int totSize)
{
	cout << "\n------------------------------------------------------\n" << endl;

	for (int i = 0; i < totSize; i++)
	{
		shapesArr[i]->show();
	}//for
}





