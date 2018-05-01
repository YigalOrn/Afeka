#ifndef __DATE_H_
#define __DATE_H_

#include <iostream>
#include <ctime>
using namespace std;

#include "DateException.h"

class Date
{
	int day;
	int month;
	int year;

	void setDayAndMonth(int n);
	int getMonthRange(int m, int y) throw (DateException);

public:
	Date(int d, int m, int y) throw (DateException);

	const Date& operator+=(int days) throw (DateException);
	friend ostream& operator<<(ostream& out, const Date& date);
	friend istream& operator>>(istream& out, Date& date) throw (DateException);
	friend Date operator+(const Date& d, int numOFDays);
	friend Date operator+(int numOFDays, const Date& d);
	bool operator==(const Date& d) const;
	void operator()(int d, int m, int y);
	bool operator<=(const Date& d) const;

	inline int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }
	void setDate(int d, int m, int y) throw (DateException);
	bool isLeapYear(int year);

	static Date* getCurrentDate();

};
#endif