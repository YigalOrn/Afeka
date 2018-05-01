#ifndef __PERSON_H_
#define __PERSON_H_

#include <iostream>
using namespace std;

class Person
{
protected:
	char* name;
	int age;

	Person(const Person& p);
	const Person& operator=(const Person& other);

public:
	Person(const char* name, int age);
	virtual ~Person();

	void setName(const char* name) throw (const char*);
	void setAge(int age) throw (const char*);
	const char* getName() const;
	int getAge() const;

	friend ostream& operator<<(ostream& out, const Person& p);
	virtual bool operator==(const Person& other) const;
};
#endif