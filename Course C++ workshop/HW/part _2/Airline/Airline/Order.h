#ifndef __ORDER_H_
#define __ORDER_H_

#include "Ticket.h"
#include "Date.h"
#include <ostream>
using namespace std;

class Order
{
	Ticket** tickets;
	int maxTickets;
	int numOfTickets;
	Date orderDate;
	Customer* customer;

public:
	Order(const Date& d, const Customer* c, int maxTickets=10);
	Order(const Order& o);
	~Order();

	double getTotalCostForOrder() const;

	const Ticket** getTickets() const;
	const Date& getOrderDate() const;
	int getNumberOfTicketsInOrder() const;
	const Customer* getCustomer() const;
	
	void setCustomer(Customer* c);

	friend ostream& operator<<(ostream& out, const Order& o);
	const Order& operator+=(const Ticket& t);
	const Order& operator-=(const Ticket& t);

};
#endif