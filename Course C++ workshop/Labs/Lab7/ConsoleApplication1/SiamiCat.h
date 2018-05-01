#ifndef __SiamiCat_h
#define __SiamiCat_h

#include "Cat.h"

class SiamiCat : virtual public Cat
{

public:

	SiamiCat(const char* name, const char* mColor, float mLen, const char* foodILike);
	SiamiCat(const Cat& baseClass, const char* foodILike);
	SiamiCat(const SiamiCat& other);
	~SiamiCat();
	
	void setFood(const char* foodILike);
	const char* const getFood() const;
	
	
	//will not work when using polymorphism!!!! <<<--------------------------
	//supports multiple assignment
	//call baseClass operator=, if needed!
	SiamiCat& operator=(const SiamiCat& other);
	friend ostream& operator<<(ostream& os, const SiamiCat& other);

private:

	char* foodILike;

};


#endif//__SiamiCat_h