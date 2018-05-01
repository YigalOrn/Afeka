#include <iostream>
using namespace std;

#include "entry.h"

Entry::Entry(const string& name, const string& adddress, const string& phone)
{
	this->name = name;
	this->address = address;
	this->phone = phone;
}

void Entry::show() const
{
	cout << "\tName: " << name.c_str() 
		 << "\n\tAddress: " << address.c_str() 
		 << "\n\tPhone: " << phone.c_str() << endl;
}

IComponent* Entry::clone() const
{
	return new Entry(*this);
}
