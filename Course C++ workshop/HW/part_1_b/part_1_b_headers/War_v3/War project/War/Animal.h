#ifndef __Animal_h
#define __Animal_h

#include <iostream>
using namespace std;


//#include "Soldier.h"//in cpp
#include "HealthState.h"
#include "AmmunitionType.h"


//forward deceleration
class Soldier;


class Animal
{

	friend ostream& operator<< (ostream& os, const Animal& animal);


public:

	//sorting animals array
	bool operator<= (const Animal& animal);

	//the hit method/operation
	virtual void operator- (Soldier& soldier) = 0;

	virtual void show(ostream& os) const = 0;


protected:

	//c'tor
	Animal(char* name, int amountOfSoldiersKilled = 0);

	//virtual d'tor
	virtual ~Animal();

	void setAmountOfSoldiersKilled(int name);

	int getAmountOfSoldiersKilled() const;

private:

	/*utility methods*/
	void setName(int name);

	const char* getName() const;


	/*not allowed*/
	Animal(const Animal& animal);
	const Animal& operator=(const Animal& other);

	char* name;
	int amountOfSoldiersKilled;

};



#endif//__Animal_h