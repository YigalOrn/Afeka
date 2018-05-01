#ifndef __DATE_H_
#define __DATE_H_

#include <ostream>
using namespace std;

class Date
{
	int day;
	int month;
	int year;

public:
	Date(int d, int m, int y);

	void setDate(int d, int m, int y);

	bool isLeapYear();

	const Date& operator+=(int days);

	friend ostream& operator<<(ostream& out, const Date& date);
	friend Date operator+(const Date& d, int numOFDays);
	friend Date operator+(int numOFDays, const Date& d);

	bool operator==(const Date& d) const;
	void operator()(int d, int m, int y);

	int getDay() const;
	int getMonth() const;
	int getYear() const;

};
#endif