#ifndef __Rifle_h
#define __Rifle_h



class Rifle
{

public:

	//c'tor
	Rifle(int bulletsAmount = 0);


	void fire();

	void setBulletsAmount(int bulletsAmount);

	int getBulletsAmount() const;


private:

	/*utility methods*/
	void incrementBulletsAmount(int amount);

	void decrementBulletsAmount(int amount);

	/*not allowed*/
	Rifle(const Rifle& rifle);
	const Rifle& operator=(const Rifle& other);


	int bulletsAmount;
};




#endif//__Rifle_h