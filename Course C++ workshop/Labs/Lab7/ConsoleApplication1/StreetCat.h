#ifndef __StreetCat_h
#define __StreetCat_h

#include "Cat.h"

class StreetCat : virtual public Cat
{

public:

	StreetCat(const char* name, const char* mColor, float mLen, int numOfStreetFights);
	StreetCat(const Cat& baseClass, int numOfStreetFights);
	StreetCat(const StreetCat& other);

	void setNumOfStreetFights(const int numOfFights);
	int getNumOfStreetFights() const;


	//supports multiple assignment
	//call baseClass operator=, if needed!
	StreetCat& operator=(const StreetCat& other);
	friend ostream& operator<<(ostream& os, const StreetCat& other);

private:

	int numOfStreetFights;

};


#endif//__StreetCat_h