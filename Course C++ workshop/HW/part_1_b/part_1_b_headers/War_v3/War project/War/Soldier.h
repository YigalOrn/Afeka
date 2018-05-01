#ifndef __Soldier_h
#define __Soldier_h


#include <iostream>
using namespace std;

#include "HealthState.h"
//#include "Animal.h"//in cpp

//forward deceleration
class Animal;

class Soldier
{
	//using virtual show()
	friend ostream& operator<< (ostream& os, const Soldier& soldier);
	
public:

	/*class interface*/

	void setHealthState(HealthState healthState);

	void setFoodKgAmount(float foodKgAmount);

	void setName(float name);

	HealthState getHealthState() const;

	float getFoodKgAmount() const;

	const char& getName() const;

	void operator+= (float foodAmount);

	void operator-= (float foodAmount);

	//for sorting soldiers array
	bool operator<= (const Soldier&) const;

	virtual void operator+= (int ammunitionAmount) = 0;

	//notice this method is not const because attacking has side affects on the attacker like :
	//ammunition, hunger and other class parameters
	virtual void operator- (Animal&) = 0;

	//for use with friends in io's
	virtual const char* show(ostream&) const = 0;

protected:

	//c'tor
	Soldier(char* name, int armyNumber, HealthState healthState = HealthState::HEALTHY, 
		float foodKgAmount = 0);

	//virtual d'tor
	virtual ~Soldier();


private:

	/*not allowed*/
	Soldier(const Soldier& soldier);
	const Soldier& operator=(const Soldier& other);


	//notice : we chose to make all base fields private thus available with geters and seters only

	char* name;
	int armyNumber;
	//an enum
	HealthState healthState;
	float foodKgAmount;


};




#endif//__Soldier_h