#ifndef __Pilot_h
#define __Pilot_h


#include <iostream>
using namespace std;


#include "Soldier.h"
#include "Animal.h"
#include "FighterAirCraft.h"
#include "AmmunitionType.h"
#include "HealthState.h"


class Pilot : public Soldier
{

public:

	//c'tor
	Pilot(char* name, int armyNumber, HealthState healthState = HealthState::HEALTHY, float foodKgAmount = 0, int numOfHoursFlied = 0);


	void setNumOfHoursFlied(int numOfHoursFlied);

	int getNumOfHoursFlied();

	void refuel(int amount);


	/*over ride*/

	//supply rockets
	void operator+= (int ammunitionAmount)override;

	// fire rockets
	void operator- (Animal& animal)override;

	//using base friend for io
	const char* show(ostream& os) const override;


private:

	/*not allowed*/
	Pilot(const Pilot& pilot);
	const Pilot& operator=(const Pilot& other);


	static const int MAX_ROCKETS;  // for example 5
	static const char lineUpSign; // for example '$'

	int numOfHoursFlied;
	//black composition
	FighterAirCraft fighterAirCraft;

};


#endif//__Pilot_h