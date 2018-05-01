#ifndef __PERSON_H_
#define __PERSON_H_

#include <iostream>
#include <string>
using namespace std;

class Person
{
protected:
	string name;
	int age;

	Person(const Person& p);
	const Person& operator=(const Person& other);

public:
	Person(const string& newName, int age);
	virtual ~Person();

	void setName(const string& newName) throw (const string&);
	void setAge(int age) throw (const char*);
	const string& getName() const;
	int getAge() const;

	friend ostream& operator<<(ostream& out, const Person& p);
	virtual bool operator==(const Person& other) const;
};
#endif