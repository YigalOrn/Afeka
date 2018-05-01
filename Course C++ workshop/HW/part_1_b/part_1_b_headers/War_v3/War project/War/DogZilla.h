#ifndef __DogZilla_h
#define __DogZilla_h

#include <iostream>
using namespace std;


#include "Animal.h"
#include "Soldier.h"


class DogZilla : virtual public Animal
{


public:

	//c'tor
	DogZilla(char* name, int amountOfSoldiersKilled, int stomachSize = 5);

	//eats a soldier, uses utility methods
	void operator- (Soldier& soldier);

	void show(ostream& os) const;


private:

	/*utility methods*/
	int getStomachSize() const;

	void setStomachSize(int stomachSize);


	/*not allowed*/
	DogZilla(const DogZilla& dogZilla);
	const DogZilla& operator=(const DogZilla& other);


	static const int MAX_STOMACH_SIZE;  // for example 10 people
	static const char lineUpSign; // for example '$'

	int stomachSize;

};


#endif//__DogZilla_h