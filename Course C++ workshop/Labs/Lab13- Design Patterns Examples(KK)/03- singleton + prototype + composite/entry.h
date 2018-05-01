#ifndef __ENTRY_H
#define __ENTRY_H

#include "component.h"

class Entry : public IComponent
{
public:
	Entry(const string& name, const string& adddress, const string& phone);
	
	virtual void show() const; // in usage of composite design pattern
	virtual IComponent* clone() const; // for prototype design pattern

private:
	string name;
	string address;
	string phone;
};

#endif // __ENTRY_H