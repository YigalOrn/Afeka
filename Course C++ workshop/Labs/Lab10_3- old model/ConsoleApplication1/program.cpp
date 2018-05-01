

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
	void loadShapesFromFile();

	saveShapes();


	cout << "\n\n" << "#########################################" << endl;
	system("PAUSE");
	cout << "#########################################" << "\n\n";


	loadShapesFromFile();



	return 0;
}//main

void saveShapes()
{
	//prototypes
	void readShapes(Shape**&, int);
	void saveShapesToFile(Shape**&, int);
	void freeShapesArr(Shape**&, int);

	int numOfShapes = 0;

	cout << "Enter how many shapes: " << endl;
	cin >> numOfShapes;

	Shape** shapesArr = new Shape*[numOfShapes];

	//init shapes array
	readShapes(shapesArr, numOfShapes);

	//write shapes to text file
	saveShapesToFile(shapesArr, numOfShapes);

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

void saveShapesToFile(Shape**& shapesArr, int size)
{

	fstream fst;
	fst.open("shapes.cplusplus", ios::out | ios::binary | ios::trunc);


	//if (!fst) {/*checks if file stream objects is open*/}


	fst.write((const char*)&size, sizeof(size));

	for (int i = 0; i < size; i++)
	{

		//save shape type using special independent method
		shapesArr[i]->saveShapeClassToFile(fst);

		
		//when using binary files, the "endl" when cascading is allowed causes the formated read 
		//i.e using the sizeof operator afterwards to mistook when reading the file!!!  
		//fst << (*shapesArr[i])<<endl;
		

		//save shape info
		fst << (*shapesArr[i]);

	}//for


	fst.close();

}

void loadShapesFromFile()
{

	//prototypes
	void showShapesAfterLoadingFromFile(Shape**, int);
	void freeShapesArr(Shape**&, int);

	//file object
	fstream fst;
	fst.open("shapes.cplusplus", ios::in | ios::binary);


	int numOfShapes;
	fst.read((char*)&numOfShapes, sizeof(numOfShapes));

	//cout << "DEBUG: program - numOfShapes  " << numOfShapes << endl;//DEBUG


	//create shapes pointer-array
	Shape** shapesArr = new Shape*[numOfShapes];


	//load each shape
	for (int i = 0; i < numOfShapes; i++)
	{

		int len;
		fst.read((char*)&len, sizeof(len));

		//cout << "DEBUG: program - len  " << len << endl;//DEBUG


		char* type = new char[len + 1];
		fst.read((char*)type, sizeof(char)*len);
		type[len] = '\0';


		//cout << "DEBUG: program - type  " << type << endl;//DEBUG


		if (strcmp(type, "Circle") == 0)
		{
			shapesArr[i] = new Circle(fst);
		}
		else if (strcmp(type, "Square") == 0)
		{
			shapesArr[i] = new Square(fst);
		}

		delete[]type;

	}//for


	fst.close();

	//show shapes after loading
	showShapesAfterLoadingFromFile(shapesArr, numOfShapes);

	//free allocated memory
	freeShapesArr(shapesArr, numOfShapes);

}//loadShapesFromFile

void showShapesAfterLoadingFromFile(Shape** shapesArr, int size)
{
	for (int i = 0; i < size; i++)
	{
		//shapesArr[i]->show();
		
		cout << *shapesArr[i] << endl;

		if (typeid(*shapesArr[i]) == typeid(Square))
		{
			Square *temp = static_cast<Square*>(shapesArr[i]);
			temp->draw();
		}//if
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




