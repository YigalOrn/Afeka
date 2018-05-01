#ifndef __CUSTOMER_H_
#define __CUSTOMER_H_

#include "Person.h"
#include <ostream>
using namespace std;


class Customer : public Person
{
	static int memberIdCounter;
	int memberId;

public:
	Customer(const Person& p);

	friend ostream& operator<<(ostream& out, const Customer& c);

	virtual bool operator==(const Customer& customer) const;

	int getMemberId() const { return memberId; }

private:
	//Customer(const Customer& c);
	const Customer& operator=(const Customer& c);
};
#endif


//********************************************
// Need to write this in the CPP
// int Customer::memberIdCounter = 1000;