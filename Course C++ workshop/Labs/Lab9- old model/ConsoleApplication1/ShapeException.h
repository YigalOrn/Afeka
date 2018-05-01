#ifndef __ShapeException_h
#define __ShapeException_h


class ShapeException 
{
	friend ostream& operator<<(ostream& os, const ShapeException & shapeException);

public:

	ShapeException(int thickness);
	
	virtual void toOs(ostream& os) const;

protected:

	int thickness;
	

};




#endif//__ShapeException_h

