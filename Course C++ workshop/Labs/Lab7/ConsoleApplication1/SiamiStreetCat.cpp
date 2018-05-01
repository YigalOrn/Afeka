#include <iostream>
using namespace std;

#include "SiamiStreetCat.h"

SiamiStreetCat::SiamiStreetCat(char* name, char* mColor, float mLen, int numOfStreetFights, char* foodILike) :
Cat(name, mColor, mLen),
StreetCat(name, mColor, mLen, numOfStreetFights),
SiamiCat(name, mColor, mLen, foodILike)
{
	/*no paramters for this class*/
}

SiamiStreetCat::SiamiStreetCat(const StreetCat& streetCat, const SiamiCat& siamiCat) :
Cat(streetCat)/*goes to copy-ctor, derived to base by ref !!*/,
StreetCat(streetCat),
SiamiCat(siamiCat)
{
	/*no paramters for this class*/
}

SiamiStreetCat::SiamiStreetCat(const SiamiStreetCat& other) :
Cat(other)/*goes to copy-ctor, derived to base by ref !!*/,
StreetCat(other),
SiamiCat(other)
{
	/*no paramters for this class*/
}

ostream& operator<<(ostream& os, const SiamiStreetCat& siamiStreetCat)
{
	os << "SiamiStreetCat :: " << endl;
	os << (Cat&)siamiStreetCat << endl;
	os << (StreetCat&)siamiStreetCat << endl;
	os << (SiamiCat&)siamiStreetCat << endl;

	return os;
}