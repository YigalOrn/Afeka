#include <iostream>
using namespace std;

#include "Tribe.h"


/*C'tor*/
Tribe::Tribe(const char* tribeName, const int& maxSurvivors)
{
	this->tribeName = new char[strlen(tribeName) + 1];
	memcpy(this->tribeName, tribeName, strlen(tribeName) + 1);
	
	this->maxSurvivors = maxSurvivors;
	this->tribeSurvivors = new Survivor*[maxSurvivors];
	this->leftSurvivors = 0;
}
/*D'tor*/
Tribe::~Tribe()
{
	delete []tribeName;
	
	for (int i = 0; i < leftSurvivors; i++)
	{
		delete tribeSurvivors[i];
	}

	delete []tribeSurvivors;

	cout << "\nIn Tribe::D'tor\n" << endl;

}

void Tribe::freeMem()
{

	for (int i = 0; i < leftSurvivors; i++)
	{
		delete tribeSurvivors[i];
	}

	delete []tribeSurvivors;
}

void Tribe::showTribe() const
{
	cout << "Tribe " << this->tribeName << " memebers :" << endl;
	cout << "\n\n----------------------------\n\n" << endl;
	for (int i = 0; i < leftSurvivors; i++)
	{
		this->tribeSurvivors[i]->showSurvivor();
	}
	cout << "\n\n----------------------------\n\n" << endl;

}

bool Tribe::eliminateSurvivor(const char const * name)
{

	if (leftSurvivors == 0)
	{
		cout << "Tribe is empty" << endl;
		return false;
	}
	else
	{
		Survivor *temp = NULL;
		int i;

		for (i = 0; i < leftSurvivors; i++)
		{
			if (strcmp(name, tribeSurvivors[i]->getName()) == 0)
			{
				temp = tribeSurvivors[leftSurvivors - 1];
				tribeSurvivors[leftSurvivors - 1] = tribeSurvivors[i];
				tribeSurvivors[i] = temp;

				delete tribeSurvivors[leftSurvivors - 1];

				leftSurvivors--;

				return true;
			}
		}

		cout << "# Not in tribe #" << endl;
		return false;
	}
}

bool Tribe::addSurvivor()
{
	//prototype
	Survivor* initSingleSurvivor(Survivor*& survivor);

	if (leftSurvivors == maxSurvivors)
	{
		cout << "# This tribe is at max capacity #" << endl;
		return false;
	}
	else
	{
		tribeSurvivors[leftSurvivors] = initSingleSurvivor(tribeSurvivors[leftSurvivors]);
		leftSurvivors++;
		return true;
	}

	return false;
}

Survivor* initSingleSurvivor(Survivor*& survivor)
{
	char name[21];
	float age;
	float initialWeight;
	int n;


	cout << "Enter survivor name :\n";
	cin >> name;

	cout << "Enter age :\n";
	cin >> age;

	cout << "Enter initial weight :\n";
	cin >> initialWeight;

	cout << "Enter status (0-single, 1-merried, 2-realtionship) :\n";
	cin >> n;

	return new Survivor(name, age, initialWeight, (Survivor::status)n);

}



