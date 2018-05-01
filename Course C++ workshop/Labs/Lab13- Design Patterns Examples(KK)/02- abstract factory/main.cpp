#include <iostream>
using namespace std;

/*
This example demonstartes the Abstract Factory pattern
*/

class IHerbivore
{
protected:
	IHerbivore() {}
public:
	virtual ~IHerbivore() {} // WHY DO WE NEED THE VIRTUAL D'TOR??
};

class ICarnivore
{
protected:
	ICarnivore() {}
public:
	virtual ~ICarnivore() {}

	virtual void eat(IHerbivore* h) 
	{
		// Eat Wildebeest - or any other Harbivore type
		cout << typeid(*this).name() << " eats " << typeid(*h).name() << endl;
	}
};

class Wildebeest : public IHerbivore
{
};

class Lion : public ICarnivore
{
};

class Bison : public IHerbivore
{
};

class Wolf : public ICarnivore
{
};

class IContinentFactory
{
public:
	virtual ~IContinentFactory() {}

	virtual IHerbivore* createHerbivore() = 0;	
	virtual ICarnivore* createCarnivore() = 0;
};


class AfricaFactory : public IContinentFactory
{
public:
	virtual IHerbivore* createHerbivore()	{return new Wildebeest();}
	virtual ICarnivore* createCarnivore()	{return new Lion();}
};

class AmericaFactory : public IContinentFactory
{
public:
	virtual IHerbivore* createHerbivore()	{return new Bison();}
	virtual ICarnivore* createCarnivore()	{return new Wolf();}
};

class AnimalWorld
{
public:
	AnimalWorld(IContinentFactory& factory)
	{
		carnivore = factory.createCarnivore();
		herbivore = factory.createHerbivore();
	}

	~AnimalWorld()
	{
		delete herbivore;
		delete carnivore;
	}

	void runFoodChain()
	{
		carnivore->eat(herbivore);
	}

private:
	IHerbivore* herbivore;
	ICarnivore* carnivore;
};

void main()
{
	// Create and run the Africa animal world 
	IContinentFactory* africa = new AfricaFactory();
	AnimalWorld world1(*africa);
	world1.runFoodChain();

	// Create and run the America animal world 
	IContinentFactory* america = new AmericaFactory();
	AnimalWorld world2(*america);
	world2.runFoodChain();

	delete africa;
	delete america;
}
