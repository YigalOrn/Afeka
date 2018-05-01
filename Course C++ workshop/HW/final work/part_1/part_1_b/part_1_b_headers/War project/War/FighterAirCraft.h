#ifndef __FighterAirCraft_h
#define __FighterAirCraft_h


class FighterAirCraft
{
public:

	//c'tor
	FighterAirCraft(int nuclearFuelLiters = 0, int numOfRockets = 0, int numOfHoursFlied = 0);


	void fire();

	void setBulletsAmount(int bulletsAmount);

	void setNumOfRockets(int numOfRockets);

	void setNumOfHoursFlied(int numOfHoursFlied);

	int getNuclearFuelLiters() const;

	int getNumOfRockets() const;

	int getNumOfHoursFlied() const;


private:

	/*utility functions*/
	void incrementBulletsAmount(int amount);
	
	void decrementBulletsAmount(int amount);


	/*not allowed*/
	FighterAirCraft(const FighterAirCraft& fighterAirCraft);
	const FighterAirCraft& operator=(const FighterAirCraft& other);


	int nuclearFuelLiters;
	int numOfRockets;
	int numOfHoursFlied;

};



#endif//__FighterAirCraft_h