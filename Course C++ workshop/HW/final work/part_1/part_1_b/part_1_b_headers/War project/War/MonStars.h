#ifndef __MonStars_h
#define __MonStars_h

#include <iostream>
using namespace std;

#include "Animal.h"
#include "AmmunitionType.h"

class MonStars
{
	//shows Monstars instance statistics
	friend ostream& operator<< (ostream& os, const MonStars& monstars);

public:

	//c'tor
	MonStars(const char* monStarsName);
	
	//d'tor
	~MonStars();

	void setMonStarsName(char* monStarsName);

	const char* getMonStarsName() const;

	void supplyAmmunition(AmmunitionType ammunitionType);

	void operator+= (Animal& animal);

	Animal& operator[] (int index);


private:

	/*utility method*/
	void sortMonStarsArray() const;
	
	void setSize(int);

	void setCurrSize(int);

	int getSize() const;

	int getCurrSize() const;


	/*not allowed*/
	MonStars(const MonStars& monStars);
	const MonStars& operator=(const MonStars& other);


	char* monStarsName;
	Animal** monStars;
	//to manage monStars array
	int size;
	int currSize;

};



#endif//__MonStars_h