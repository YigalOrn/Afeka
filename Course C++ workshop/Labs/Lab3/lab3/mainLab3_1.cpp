#include<iostream>
using namespace std;

#include "Survivor.h"



/*
int main(void)
{
	//prototypes
	void initTribesData(Survivor **&, const int&);//ref type cannot change memory address!
	void showTribe(Survivor **&, const int&);
	void freeTribeMemory(Survivor **&, const int&);

	int numOfSurvivors;




	cout << "How many survivors?" << endl;
	cin >> numOfSurvivors;

	Survivor **survivorArr1 = new Survivor*[numOfSurvivors];
	//Survivor **survivorArr1 = (Survivor **)malloc(sizeof(Survivor)*numOfSurvivors);
	initTribesData(survivorArr1, numOfSurvivors);

	cout << "\n\n--------------------------\n" << endl;

	Survivor **survivorArr2 = new Survivor*[numOfSurvivors];
	initTribesData(survivorArr2, numOfSurvivors);

	cout << "\n\n++++++++++++++++++++++++++++++++++++++\n" << endl;


	cout << "Tribe 1 :" << endl;
	showTribe(survivorArr1, numOfSurvivors);

	cout << "--------------------------\nTribe 2 :" << endl;
	showTribe(survivorArr2, numOfSurvivors);

	cout << "--------------------------\n\nFree memory....\n\n" << endl;
	freeTribeMemory(survivorArr1, numOfSurvivors);
	freeTribeMemory(survivorArr2, numOfSurvivors);

	return 0;
}



void initTribesData(Survivor **& survivorArr, const int &numOfSurvivors)
{
	//prototype
	void initSingleSurvivor(Survivor*& survivor);

	for (size_t i = 0; i < numOfSurvivors; i++)
	{
		survivorArr[i] = new Survivor;
		//*(survivorArr+i)= new Survivor;
		initSingleSurvivor(survivorArr[i]);
	}

}
void initSingleSurvivor(Survivor*& survivor)
{
	char name[21];
	float age;
	float initialWeight;
	int n;
	Survivor::status st;

	cout << "Enter survivor name :\n";
	cin >> name;

	cout << "Enter age :\n";
	cin >> age;

	cout << "Enter initial weight :\n";
	cin >> initialWeight;

	cout << "Enter status (0-single, 1-merried, 2-realtionship) :\n";
	cin >> n;

	

	survivor->initSurvivor(name, age, initialWeight, (Survivor::status)n);

}


void showTribe(Survivor **& survivorArr, const int &numOfSurvivors)
{
	for (size_t i = 0; i < numOfSurvivors; i++)
	{
		survivorArr[i]->showSurvivor();
	}

}

void freeTribeMemory(Survivor **& survivorArr, const int &numOfSurvivors)
{

	for (size_t i = 0; i < numOfSurvivors; i++)
	{
		delete survivorArr[i];
	}

	delete[]survivorArr;

}
*/