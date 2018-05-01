#ifndef __War_h
#define ___War_h

#include <iostream>
using namespace std;


#include "Army.h"
#include "MonStars.h"
#include "Soldier.h"
#include "Animal.h"
#include "AmmunitionType.h"

class War
{

	//shows statistics
	friend ostream& operator<< (ostream& os, const War& war);


public:

	//c'tor
	War(Army* const army, MonStars* const monStars);

	//d'tor
	~War();

	bool areWeAtWar() const;

	void setWarStarted(bool isWarStarted);

	void finishWar();

	void supplyAmmunition(AmmunitionType ammType);

	void refuelAirCraft(int amount);

	void feedForce(float foodKgAmount);

	void addSoldier(Soldier* const soldier);

	void addAnimal(Animal* const animal);

	char* lineUpTheTroops(void) const;

	char* hit();


private:

	/*utility methods*/
	void setArmies(Army& army, MonStars& monstars);

	Army& getArmy();

	MonStars& getMonStars();


	/*not allowed*/
	War(const War& war);
	const War& operator=(const War& other);

	Army* army;
	MonStars* monStars;
	bool isWarStarted;




};


#endif//___War_h