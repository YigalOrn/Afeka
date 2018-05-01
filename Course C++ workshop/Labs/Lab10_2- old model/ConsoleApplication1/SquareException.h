#ifndef __SquareException_h
#define __SquareException_h

#include "ShapeException.h"

class SquareException :public ShapeException
{


public:

	SquareException(int thickness, int width);

	virtual void toOs(ostream& os) const override;

private:

	int width;

};




#endif//__SquareException_h











