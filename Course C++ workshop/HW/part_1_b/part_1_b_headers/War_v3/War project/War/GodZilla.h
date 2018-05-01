#ifndef __GodZilla_h
#define __GodZilla_h


#include "Animal.h"
#include "Soldier.h"
#include "DogZilla.h"
#include "SiamAmurai.h"



class GodZilla : public DogZilla, public SiamAmurai
{

public:

	//c'tor
	GodZilla(char* name, int amountOfSoldiersKilled, int stomachSize = 5, int clutchesSharpness = 5, int fireHeatPower = 5);

	//this creature can choose from 3 methods randomly(2 derives and himself), uses utility methods
	void operator- (Soldier& soldier);

	void show(ostream& os) const;


private:

	/*utility methods*/
	int getFireHeatPower() const;

	void setFireHeatPower(int fireHeatPower);


	/*not allowed*/
	GodZilla(const GodZilla& godZilla);
	const GodZilla& operator=(const GodZilla& other);


	static const int MAX_FIRE_BALLS;
	static const char lineUpSign; // for example '$'

	int fireHeatPower;

};



#endif//__GodZilla_h