#ifndef __Army_h
#define __Army_h


#include <iostream>
using namespace std;


#include "Soldier.h"
#include "AmmunitionType.h"


class Army
{
	//shows Army instance statistics
	friend ostream& operator<< (ostream& os, const Army& army);

public:

	//c'tor
	Army(const char* armyName);
	
	//d'tor
	~Army();

	//uppon selection of type at main the logic will refresh all fighter ammo stock respectively
	void supplyAmmunition(AmmunitionType ammunitionType);

	//adds a soldier to the soldiers array, sorting is required
	void operator+= (Soldier& soldier);

	//get a soldier from the soldiers array using arrays notation
	Soldier& operator[] (int index);


private:

	/*utility method*/
	void sortSoldiersArray() const;

	void setArmyName(const char* armyName);

	void setSize(int);

	void setCurrSize(int);


	int getSize() const;

	int getCurrSize() const;

	const char* getArmyName() const;


	/*not allowed*/
	Army(const Army& army);
	const Army& operator=(const Army& other);


	char* armyName;
	Soldier** soldiers;
	//to manage soldiers array
	int size;
	int currSize;

};



#endif//__Army_h