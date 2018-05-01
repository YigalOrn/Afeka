#include<iostream>
using namespace std;

#include "Tribe.h"
#include "Survivor.h"



int main(void)
{
	
	
	char tribeName[21];
	int maxSurvivors;

	cout << "Enter tribe size: " << endl;
	cin >> maxSurvivors;


	cout << "Enter tribe1 name: " << endl;
	cin >> tribeName;
	Tribe *tribe1 = new Tribe(tribeName, maxSurvivors);
	


	cout << "Enter tribe2 name: " << endl;
	cin >> tribeName;
	Tribe *tribe2 = new Tribe(tribeName, maxSurvivors);
	


	tribe1->showTribe();
	tribe2->showTribe();


	cout << "Adding new member to tribe1: \n" << endl;
	tribe1->addSurvivor();

	cout << "Adding 2 new members to tribe2: \n" << endl;
	tribe2->addSurvivor();
	tribe2->addSurvivor();


	tribe1->showTribe();
	tribe2->showTribe();


	cout << "Eliminate a survivor from tribe1 :\n" << endl;
	cin >> tribeName;
	tribe1->eliminateSurvivor("Rocket");
	tribe1->eliminateSurvivor(tribeName);
	tribe1->eliminateSurvivor("Cat");


	tribe1->showTribe();
	tribe2->showTribe();


	delete tribe1;
	delete tribe2;
	
	return 0;
}



