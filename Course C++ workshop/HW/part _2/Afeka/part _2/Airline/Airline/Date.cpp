#include <iostream>
#include <ctime>
using namespace std;

#include "Date.h"


Date::Date(int d, int m, int y)
{
	setDate(d, m, y);
}

void Date::setDate(int d, int m, int y)
{

	time_t timeVar = time(0);
	struct tm timeStruct;
	localtime_s(&timeStruct, &timeVar);


	if (y < timeStruct.tm_year + 1900)
	{
		//throw exception : making a date that will not occur
		cout << "#Date Exception " << __LINE__ << endl;
		exit(1);
	}

	if (m < 1 || 12 < m)
	{
		//throw exception : invalid month
		cout << "#Date Exception " << __LINE__ << endl;
		exit(1);
	}

	if (getMonthRange(m, y) < d)
	{
		//throw exception : day is out of month range
		cout << "#Date Exception " << __LINE__ << endl;
		exit(1);
	}

	if ((y == (timeStruct.tm_year + 1900)) &&
		((m < (timeStruct.tm_mon + 1)) ||
			(d < timeStruct.tm_mday)))
	{

		//throw exception : making a date that will not occur
		cout << "#Date Exception " << __LINE__ << endl;
		exit(1);
	}


	day = d;
	month = m;
	year = y;

}

bool Date::isLeapYear(int y)
{
	if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

const Date& Date::operator+=(int days)
{
	if (days < 0)
	{
		//throw
		cout << "#Date Exception " << __LINE__ << endl;
		exit(1);
	}
	year += static_cast<int>(days / 365);//add years

	cout << "#DEBUG  : days%365 = " << days % 365 << endl;
	setDayAndMonth(days % 365);

	return *this;
}

int Date::getMonthRange(int m, int y)
{
	switch (m)
	{
		// January, March, May, July, August, October and December have 31 days.
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 30;
		// April, June, September and November have 30 days
	case 4: case 6: case 9: case 11:
		return 31;
		// February has 29 days in leap years, 28 days else wise
	case 2:
		if (isLeapYear(y))
		{
			return 29;
		}
		else
		{
			return 28;
		}

	default:
		//throw exception : invalid day
		cout << "#Date Exception " << __LINE__ << endl;
		exit(1);
	}
}

void Date::setDayAndMonth(int n)
{
	cout << "#DEBUG :  getMonthRange(month, year) = " << getMonthRange(month, year) << endl;

	//stoping cond.
	if ((n + day) <= getMonthRange(month, year))
	{
		day += n;
		return;
	}

	month++;
	if (month == 13) { month = 1; }

	int lastDay = day;
	day = 0;

	//recursion step
	setDayAndMonth(n - (getMonthRange(month - 1, year) - lastDay));
}

ostream& operator<<(ostream& out, const Date& date)
{
	if (date.day < 10)
	{
		out << "0";
	}
	out << date.day << "/";


	if (date.month < 10)
	{
		out << "0";
	}
	out << date.month << "/";


	return out << date.year;
}

Date operator+(const Date& d, int numOFDays)
{
	Date temp(d);
	temp.setDayAndMonth(numOFDays);
	return temp;
}

Date operator+(int numOFDays, const Date& d)
{
	return (d + numOFDays);
}

bool Date::operator==(const Date& d) const
{
	return (d.year == year && d.month == month && d.day == day);
}

void Date::operator()(int d, int m, int y)
{
	setDate(d, m, y);
}







