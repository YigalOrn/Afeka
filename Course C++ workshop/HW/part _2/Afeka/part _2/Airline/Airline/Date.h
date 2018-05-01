#ifndef __DATE_H_
#define __DATE_H_

#include <iostream>
using namespace std;

class Date
{
	int day;
	int month;
	int year;

	void setDayAndMonth(int n);
	int getMonthRange(int m, int y);

public:
	Date(int d, int m, int y);

	void setDate(int d, int m, int y);

	//bool isLeapYear();

	bool isLeapYear(int year);

	const Date& operator+=(int days);

	friend ostream& operator<<(ostream& out, const Date& date);

	friend Date operator+(const Date& d, int numOFDays);

	friend Date operator+(int numOFDays, const Date& d);

	bool operator==(const Date& d) const;

	void operator()(int d, int m, int y);

	inline int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }

};
#endif