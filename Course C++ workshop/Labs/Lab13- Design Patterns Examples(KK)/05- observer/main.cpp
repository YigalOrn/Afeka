#include <iostream>
#include <algorithm>
using namespace std;

#include "array.h"

class IObserver
{
public:
	IObserver(const string& name) : name(name) {}
	virtual void notify(const string& name, int precentage) const = 0;
	virtual IObserver* clone() const =0;
	const string& getName() const {return name;}
protected:
	string name;
}; // IObserver

class Shop {
public:
	Shop(const string& name) : name(name) {}

	void registerObserver(IObserver* obs) 
	{
		cout << "Registerd " << obs->getName().c_str() << " to get notifications from '" << name.c_str() << "'\n";
		viewers.add(*obs);
	}
	void setSail(int precenatge) 
	{
		cout << "Set " << precenatge << "% sail on '" << name.c_str() << "'\n";
		notifyAllRegistered(precenatge);
	}

private:
	void notifyAllRegistered(int precenatge) const
	{
		int size = viewers.count();
		for (int i=0 ; i < size ; i++)
			viewers[i].notify(name, precenatge);
	}

	string name;
	Array<IObserver> viewers; 
};

class Customer : public IObserver 
{
public:
	Customer(const string& name) : IObserver(name) {}
	virtual void notify(const string& shopName, int precentage) const
	{
		cout << name.c_str() << "! There is " << precentage << "% sail on '" << shopName.c_str() << "'\n";
	}

	virtual IObserver* clone() const {return new Customer(*this);}
};

class Newspaper : public IObserver 
{
public:
	Newspaper(const string& name) : IObserver(name) {}
	virtual void notify(const string& shopName, int precentage) const
	{
		cout << "The newspaper " << name.c_str() << " prints add that there is " << precentage << "% sail on '" << shopName.c_str() << "'\n";
	}

	virtual IObserver* clone() const {return new Newspaper(*this);}
};


void main() 
{
	Shop s1("Renuar");
	Shop s2("Hanes");
	Shop s3("Castro");

	Customer c1("Gogo");
	Customer c2("Momo");
	Newspaper n1("Yediot");
	Newspaper n2("Ma'ariv");

	s1.registerObserver(&c1);
	s1.registerObserver(&c2);
	s1.registerObserver(&n1);
	s1.registerObserver(&n2);

	s2.registerObserver(&c1);
	s2.registerObserver(&n1);
	s3.registerObserver(&n2);

	s3.registerObserver(&c2);
	s3.registerObserver(&n1);
	s3.registerObserver(&n2);
	cout << "\n";

	s1.setSail(50);
	s2.setSail(20);
	s3.setSail(30);
	cout << "\n";
}