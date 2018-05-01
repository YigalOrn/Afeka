#ifndef __CUSTOMER_H_
#define __CUSTOMER_H_

#include <iostream>
using namespace std;

#include "Person.h"

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
	const Customer& operator=(const Customer& c);
};
#endif
