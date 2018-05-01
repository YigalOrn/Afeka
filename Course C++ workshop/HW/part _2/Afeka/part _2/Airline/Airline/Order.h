#ifndef __ORDER_H_
#define __ORDER_H_


#include <iostream>
using namespace std;

#include "Ticket.h"
#include "Date.h"
#include "Customer.h"



class Order
{
	Ticket** tickets;
	int maxTickets;
	int numOfTickets;
	Date orderDate;
	const Customer* customer;

	void removeTicket(int ticketIndex);
	
	//Order(const Order& o);//def is not enough??

public:
	
	Order(const Date& d, const Customer* c, int maxTickets=10);
	
	
	
	~Order();

	double getTotalCostForOrder() const;

	double sumObjectFunc(double sum, Ticket* currTicket);

	const Ticket*const* getTickets() const { return tickets; }
	
	const Date& getOrderDate() const { return orderDate; }
	
	int getNumberOfTicketsInOrder() const { return numOfTickets; }
	
	const Customer* const getCustomer() const { return customer; }
	
	//void setCustomer(Customer* c);

	friend ostream& operator<<(ostream& out, const Order& o);
	
	const Order& operator+=(const Ticket& t);
	
	const Order& operator-=(const Ticket& t);

};
#endif