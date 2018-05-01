#include <iostream>
#include <numeric>
using namespace std;

#include "Order.h"


Order::Order(
	const Date& d,
	const Customer* c,
	int maxTickets = 10) :
	orderDate(d),
	customer(c),
	numOfTickets(0)
{
	//should be checked
	this->maxTickets = maxTickets;

	tickets = new Ticket*[maxTickets];
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
	/*
	double sum = 0;
	for (int i = 0; i < numOfTickets; i++)
	{
		sum += tickets[i]->getTicketCost();
	}
	return sum;
	*/

	return accumulate(tickets, tickets+numOfTickets, 0, sumObjectFunc);
}

double Order::sumObjectFunc(double sum, Ticket* currTicket) 
{
	return (sum+(currTicket->getTicketCost()));
}

ostream& operator<<(ostream& out, const Order& o)
{
	return out << "# Implement Order ostream";
}

const Order& Order::operator+=(const Ticket& t)
{
	if (numOfTickets < maxTickets)
	{
		tickets[numOfTickets++] = new Ticket(t);
	}
	else
	{
		//throw
	}

	return *this;
}

const Order& Order::operator-=(const Ticket& t)
{
	if (numOfTickets == 0)
	{
		// throw
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





