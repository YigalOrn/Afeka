#include <iostream>
#include "Customer.h"


Customer::Customer(const Person& p) : Person(p)
{
	memberId = memberIdCounter;
	memberIdCounter++;
}

ostream& operator<<(ostream& out, const Customer& c)
{
	out << "Customer name : " << c.getName() << endl;
	out << "Customer age : " << c.getAge() << endl;
	out << "Customer member ID : " << c.getMemberId() << endl;
	return out;
}

bool Customer::operator==(const Customer& customer) const
{
	return this->getMemberId() == customer.getMemberId();
}

int Customer::memberIdCounter = 1000;










