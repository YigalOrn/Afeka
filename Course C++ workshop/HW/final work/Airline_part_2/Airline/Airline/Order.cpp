#include <iostream>
#include <numeric>//for accumulate
using namespace std;

#include "Order.h"

Order::Order(
	const Date& d,
	const Customer* c,
	int maxTickets) :
	orderDate(d),
	customer(c),
	numOfTickets(0)
{
	//should be checked
	this->maxTickets = maxTickets;
	tickets = new Ticket*[maxTickets];
	orderId = orderIdCounter++;
}

Order::~Order()
{
	for (int i = 0; i < numOfTickets; i++)
	{
		delete tickets[i];
	}
	delete[]tickets;
}

double Order::getTotalCostForOrder() const
{

	double sum = 0;
	for (int i = 0; i < numOfTickets; i++)
	{
		sum += tickets[i]->getTicketCost();
	}
	return sum;
}

double Order::sumObjectFunc(double sum, Ticket* currTicket)
{
	return (sum + (currTicket->getTicketCost()));
}

ostream& operator<<(ostream& out, const Order& o)
{
	out << "Order ID: " << o.getOrderId() << endl;
	out << "Order Date: " << o.getOrderDate() << endl;
	out << "Order Customer: " << *o.getCustomer() << endl;
	return out;
}

const Order& Order::operator+=(const Ticket& t) throw (const char*)
{
	if (numOfTickets < maxTickets)
	{
		tickets[numOfTickets++] = new Ticket(t);
	}
	else
	{
		throw "# Tickets amount in the Order has exceeded max amount #";
	}

	return *this;
}

const Order& Order::operator-=(const Ticket& t) throw (const char*)
{
	if (numOfTickets == 0)
	{
		throw "# No more tickets to delete from the Order #";
	}
	else
	{
		for (int i = 0; i < numOfTickets; i++)
		{
			if (t == *tickets[i])
			{
				delete tickets[i];
				tickets[i] = nullptr;

				tickets[i] = tickets[--numOfTickets];
				tickets[numOfTickets] = nullptr;
				break;
			}
		}//for
	}
	return *this;
}

bool Order::operator==(const Order& order) const
{
	return this->getOrderId() == order.getOrderId();
}

int Order::orderIdCounter = 1;