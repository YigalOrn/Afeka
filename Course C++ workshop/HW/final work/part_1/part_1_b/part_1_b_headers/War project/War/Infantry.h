/*
http://en.cppreference.com/w/cpp/language/override
*/


#ifndef __Infantry_h
#define __Infantry_h


#include <iostream>
using namespace std;


#include "Soldier.h"
#include "Rifle.h"
#include "AmmunitionType.h"
#include "HealthState.h"


class Infantry : public Soldier
{

public:

	//c'tor
	Infantry(char* name, int armyNumber, float foodKgAmount = 0, int numOfHoursBeingAwake = 0);


	void setNumOfHoursBeingAwake(int numOfHoursBeingAwake);

	int getNumOfHoursBeingAwake() const;


	/*over ride*/

	//supply bullets
	void operator+= (int ammunitionAmount) override;

	// fire bullets
	void operator- (Animal& animal) override;

	//using base friend for io
	const char* show(ostream& os) const override;


private:

	/*not allowed*/
	Infantry(const Infantry& infantry);
	const Infantry& operator=(const Infantry& other);


	static const int MAX_BULLETS;  // for example 30
	static const char lineUpSign; // for example '#'

	int numOfHoursBeingAwake;
	//black composition
	Rifle rifle;

};




#endif//__Infantry_h