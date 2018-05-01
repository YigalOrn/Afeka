#ifndef __CATEGORY
#define __CATEGORY

#include "component.h"

class Category : public IComponent
{
public:
	static const int MAX_COMPONENTS = 100;

	Category(const string& name);
	Category(const Category& other);
	~Category();

	const Category& operator=(const Category&); 

	virtual IComponent* clone() const; // for prototype design pattern

	virtual void show() const; // in usage of composite design pattern

	void addComponent(const IComponent& newComponent); // in usage of composite design pattern
	IComponent* getComponentAtIndex(int index) const; // in usage of composite design pattern
private:
	string name;
	/*
	type is pointer because of polymorphizem i.e hetrogenic
	*/
	IComponent* components[MAX_COMPONENTS]; // in usage of composite design pattern
	int numOfComponents;
};

#endif // __CATEGORY