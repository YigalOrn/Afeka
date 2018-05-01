#ifndef __Survivor
#define __Survivor

#include"Bandana.h"

class Survivor
{

public:

	enum status { SINGLE, MERRIED, RELATIONSIP };
	
	/*C'tor*/
	Survivor(const char const *name, const float &age, const float &initialWeight, const status &st, const Bandana &bandana);
	/*D'tor*/
	~Survivor();
	/*Copy C'tor - for practice*/
	Survivor(const Survivor& other);

	void showSurvivor() const;
	

	void setName(const char const* name);
	void setAge(const float &age);
	void setInitialWeight(const float &initialWeight);
	void setFinalWieght(const float &finalWeight = -1);
	void setStatus(const status &st);
	void setBandana(const Bandana &bandana);

	const char const *  getName()const;
	const float& getAge() const;
	const status getStatus() const;
	const float& getInitialWeight() const;
	const float& getFinalWieght() const;


private:

	char* name;//one char for null-terminator
	float age;
	float initialWeight;
	float finalWeight;
	status st;
	Bandana bandana;
};

#endif


