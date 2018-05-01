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

	void setName(const char* name);
	void setAge(int age);

	const char* getName() const;
	int getAge() const;

	friend ostream& operator<<(ostream& out, const Person& p);

};
#endif