#ifndef __AirCrew_H
#define __AirCrew_H

#include <iostream>
using namespace std;

#include "Person.h"
#include "Date.h"
#include "AirCrewException.h"

class AirCrew : virtual public Person
{
private:
	//inner class
	class WorkingDatesList
	{
	public:
		WorkingDatesList() : head(NULL), tail(NULL) {}
		WorkingDatesList(const WorkingDatesList& list) : head(NULL), tail(NULL)
		{
			WorkingDateNode* srcPtr = list.head;
			WorkingDateNode *desPtr = 0, *prevDesPtr = 0;

			while (srcPtr)
			{
				desPtr = new WorkingDateNode(*srcPtr);
				if (prevDesPtr)
				{
					prevDesPtr->nextDateNode = desPtr;
				}
				else
				{
					head = desPtr;
				}
				prevDesPtr = desPtr;
				desPtr = desPtr->nextDateNode;
				srcPtr = srcPtr->nextDateNode;
			}
			tail = prevDesPtr;
		}

		//this is a public class with public members
		struct WorkingDateNode
		{
			Date workingDate;
			WorkingDateNode* nextDateNode;

			WorkingDateNode(const Date& date) : workingDate(date), nextDateNode(0) {}
			WorkingDateNode(const WorkingDateNode& other) : workingDate(other.workingDate), nextDateNode(0) {}
		};

		WorkingDateNode* head;
		WorkingDateNode* tail;

		void addDateToList(const Date& date);
		void removeDateFromList(const Date& date);
		bool isDateExistsInList(const Date& date) const;
		void freeDatesList();
	};

protected:
	WorkingDatesList datesList;

	int seniority;
	double salary;

	AirCrew(const Person& p, int seniority, double salary);
	AirCrew(const AirCrew& other);

public:
	virtual ~AirCrew();
	virtual AirCrew* clone() const = 0; // for Prototype design pattern

	friend ostream& operator<<(ostream& out, const AirCrew& ac);
	friend ostream& operator<<(ostream& out, const WorkingDatesList& datesList);

	virtual void toOs(ostream& out) const = 0;

	void setSalary(double salary) throw(AirCrewException);
	void setSeniority(int seniority) throw(AirCrewException);
	double getSalary() const;
	int getSeniority() const;
	const WorkingDatesList& getDatesList() const;

	virtual bool operator==(const Person& other) const;

	void addDateToWorkingDatesList(const Date& date);
	void removeDateFromWorkingDatesList(const Date& date);
	bool isDateAvailable(const Date& date) const;

};

#endif //__AirCrew_H