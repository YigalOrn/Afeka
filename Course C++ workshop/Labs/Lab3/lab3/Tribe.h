#ifndef __Tribe
#define __Tribe

#include "Survivor.h"

class Tribe
{

private:

	 char *tribeName;
	 int maxSurvivors;
	 Survivor **tribeSurvivors;
	 int leftSurvivors;


public:

	/*C'tor*/
	Tribe(const char*, const int&);
	/*D'tor*/
	~Tribe();

	void showTribe() const;
	bool eliminateSurvivor(const char const * name);
	bool addSurvivor();
	void freeMem();
};



#endif