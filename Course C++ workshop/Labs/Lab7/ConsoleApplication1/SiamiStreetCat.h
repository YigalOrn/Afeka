#ifndef __SiamiStreetCat_h
#define __SiamiStreetCat_h


#include "SiamiCat.h"
#include "StreetCat.h"

class SiamiStreetCat : public StreetCat, public SiamiCat
{

public:

	SiamiStreetCat(char* name, char* mColor, float mLen, int numOfStreetFights, char* foodILike);
	SiamiStreetCat(const StreetCat&, const SiamiCat&);
	SiamiStreetCat(const SiamiStreetCat& other);

	friend ostream& operator<<(ostream& os, const SiamiStreetCat& siamiStreetCat);
};


#endif//__SiamiStreetCat_h