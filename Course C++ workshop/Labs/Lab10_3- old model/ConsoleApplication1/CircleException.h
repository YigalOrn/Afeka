#ifndef __CircleException_h
#define __CircleException_h


#include "ShapeException.h"

class CircleException :public ShapeException
{


public:

	CircleException(int thickness, float radius);

	virtual void toOs(ostream& os) const;

private:

	float radius;

};




#endif//__CircleException_h

