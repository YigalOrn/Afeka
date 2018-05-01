#ifndef __SiamAmurai_h
#define __SiamAmurai_h



#include "Animal.h"
#include "Soldier.h"


class SiamAmurai : virtual public Animal
{

public:

	//c'tor
	SiamAmurai(char* name, int amountOfSoldiersKilled, int clutchesSharpness = 5);

	//scratches a soldier, uses utility methods
	void operator- (Soldier& soldier);

	void show(ostream& os) const;


private:

	/*utility methods*/
	int getClutchesSharpness() const;

	void setClutchesSharpness(int clutchesSharpness);


	/*not allowed*/
	SiamAmurai(const SiamAmurai& siamAmurai);
	const SiamAmurai& operator=(const SiamAmurai& other);


	static const int MAX_CLUTCHES_SHARPNESS;  // for example 8
	static const char lineUpSign; // for example '$'

	int clutchesSharpness;

};



#endif//__SiamAmurai_h