#include "AirCrew.h"



AirCrew::AirCrew(const Person& p, int seniority, double salary) : Person(p), seniority(seniority), salary(salary) {}

AirCrew::AirCrew(const AirCrew& other) : Person(other), seniority(other.getSeniority()), salary(other.getSalary()), datesList(other.getDatesList()){}

AirCrew::~AirCrew()
{
	datesList.freeDatesList();
}

ostream& operator<<(ostream& out, const AirCrew& ac)
{
	out << "______________________________________" << endl;
	out << typeid(ac).name() + 6 << " name : " << ac.getName() << endl;
	out << typeid(ac).name() + 6 << " age : " << ac.getAge() << endl;
	out << "Seniority: " << ac.getSeniority() << " , Salary: " << ac.getSalary() << endl;
	out << "Working dates: " << endl;
	out << ac.getDatesList();
	ac.toOs(out);
	out << "______________________________________" << endl;
	return out;
}

void AirCrew::setSalary(double salary) throw(AirCrewException)
{
	if (salary <= 0)
	{
		throw AirCrewException("# Salary cannot be negative #");
	}
	this->salary = salary;
}

void AirCrew::setSeniority(int seniority) throw(AirCrewException)
{
	if (seniority <= 0)
	{
		throw AirCrewException("# Seniority cannot be negative #");
	}
	this->seniority = seniority;
}

double AirCrew::getSalary() const
{
	return salary;
}

int AirCrew::getSeniority() const
{
	return seniority;
}

const AirCrew::WorkingDatesList& AirCrew::getDatesList() const
{
	return datesList;
}

bool AirCrew::operator==(const Person& other) const
{
	if (!(Person::operator==(other)))
	{
		return false;
	}

	const AirCrew& temp = dynamic_cast<const AirCrew&> (other);
	return (seniority == temp.getSeniority()) && (salary == temp.getSalary());
}


//for inner class

void AirCrew::addDateToWorkingDatesList(const Date& date)
{
	datesList.addDateToList(date);
}

void AirCrew::removeDateFromWorkingDatesList(const Date& date)
{
	datesList.removeDateFromList(date);
}

bool AirCrew::isDateAvailable(const Date& date) const
{
	return !datesList.isDateExistsInList(date);
}


//inner class

void AirCrew::WorkingDatesList::addDateToList(const Date& date)
{
	if (head == NULL)
	{
		head = new WorkingDateNode(date);
		tail = head;
	}
	else
	{
		WorkingDateNode* temp = new WorkingDateNode(date);
		tail->nextDateNode = temp;
		tail = temp;
	}
}

void AirCrew::WorkingDatesList::removeDateFromList(const Date& date)
{
	WorkingDateNode *ptrPre = 0, *ptrDel = 0;
	if (head == NULL) {
		return;
	}
	if (head->workingDate == date) 
	{
		ptrDel = head;
		head = ptrDel->nextDateNode;
		if (!head) 
		{
			tail = 0;
			//notice tail might be garbage when there is one node left, but head says the list is empty!
		}
		delete ptrDel;
		return;
	}
	ptrPre = head;
	ptrDel = head->nextDateNode;
	while (ptrDel != NULL)
	{
		if (ptrDel->workingDate == date) 
		{
			ptrPre->nextDateNode = ptrDel->nextDateNode;
			if (ptrDel == tail) 
			{
				tail = ptrPre;
			}
			delete ptrDel; 
			break; 
		}
		ptrPre = ptrDel;
		ptrDel = ptrDel->nextDateNode;
	}
	//if head does not equal date then go here
}

bool AirCrew::WorkingDatesList::isDateExistsInList(const Date& date) const
{
	WorkingDateNode *ptrCurr = head;
	while (ptrCurr)
	{
		if (ptrCurr->workingDate == date)
		{
			return true;
		}
		ptrCurr = ptrCurr->nextDateNode;
	}
	return false;	
}

ostream& operator<<(ostream& out, const AirCrew::WorkingDatesList& datesList)
{
	AirCrew::WorkingDatesList::WorkingDateNode* temp = datesList.head;
	while (temp)
	{
		out << temp->workingDate << endl;
		temp = temp->nextDateNode;
	}
	return out;
}

void AirCrew::WorkingDatesList::freeDatesList()
{
	WorkingDateNode *ptrDel = head, *ptrNext = head;
	
	if (head == NULL) {
		return;
	}

	while (ptrDel != NULL)
	{
		ptrNext = ptrNext->nextDateNode;
		delete ptrDel;
		ptrDel = ptrNext;
	}
}