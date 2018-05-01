#ifndef __ICOMPONENT_H
#define __ICOMPONENT_H

#include <iostream>
using namespace std;

class IComponent
{
public:
	virtual void show() const =0;  // in usage of composite design pattern
	virtual IComponent* clone() const =0; // for prototype design pattern
};

#endif // __ICOMPONENT_H