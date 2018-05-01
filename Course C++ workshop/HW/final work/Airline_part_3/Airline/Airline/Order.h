#ifndef __ORDER_H_
#define __ORDER_H_

#include <iostream>
#include <numeric> //for accumulate
#include <iterator>
#include <algorithm>
using namespace std;

#include "Ticket.h"
#include "Date.h"
#include "Customer.h"

extern double sumObjectFunc(double sum, Ticket* currTicket);


class Order
{
	friend class AirLine;

	static int orderIdCounter;
	int orderId;
	
	Date orderDate;
	Ticket** tickets;

	int maxTickets;
	int numOfTickets;
	
	const Customer* customer;
	
public:
	
	Order(const Date& d, const Customer* c, int maxTickets = 10);
	Order(const Order& order);
	~Order();

	double getTotalCostForOrder() const;
	int getOrderId() const { return orderId; }
	Ticket** getTickets() const { return tickets; }
	const Date& getOrderDate() const { return orderDate; }	
	int getNumberOfTicketsInOrder() const { return numOfTickets; }
	const Customer* const getCustomer() const { return customer; }
	int getMaxTickets() const { return maxTickets; }

	friend ostream& operator<<(ostream& out, const Order& o);
	const Order& operator+=(const Ticket& t) throw (const string&);
	const Order& operator-=(const Ticket& t) throw (const string&);
	bool operator==(const Order& order) const;
};
#endif