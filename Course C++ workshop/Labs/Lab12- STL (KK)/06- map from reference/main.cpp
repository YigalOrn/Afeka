#include <iostream>
using namespace std;

#include <map>

void main()
{
	map<const char*, int> months;

	months["january"] = 31;  months["february"] = 28;   months["march"] = 31;
	months["april"] = 30;    months["may"] = 31;        months["june"] = 30;
	months["july"] = 31;     months["august"] = 31;     months["september"] = 30;
	months["october"] = 31;  months["november"] = 30;   months["december"] = 31;

	cout << "june -> " << months["june"] << endl; // june -> 30
	map<const char*, int>::iterator cur  = months.find("june");
	map<const char*, int>::iterator prev = cur;
	map<const char*, int>::iterator next = cur;    
	++next;
	--prev;
	cout << "Previous is " << (*prev).first << endl; // Previous is july
	cout << "Next is " << (*next).first << endl;     // Next is may

	system("pause");

}
