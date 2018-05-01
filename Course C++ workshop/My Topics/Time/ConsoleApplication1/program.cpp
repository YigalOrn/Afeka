#include <iostream>
using namespace std;

#include <cstdlib>//srand, rand
#include <ctime>


int main(void)
{

	cout << "###################################" << endl;


	//------------------------------
	time_t timeVar1 = time(0);
	time_t timeVar2 = time(NULL);//same

	cout << "timeVar1 = " << timeVar1 << endl;
	cout << "timeVar2 = " << timeVar2 << endl;


	time_t timeVar3 = -1;
	time(&timeVar3);

	cout << "timeVar3 = " << timeVar3 << endl;

	//------------------------------


	cout << "###################################" << endl;


	//------------------------------

	time_t timeVar = time(0);
	//struct tm timeStruct = { timeVar };

	struct tm *timeStruct = new struct tm;
	//localtime_s(timeStruct, &timeVar);


	//struct tm tm = *localtime(&(time_t) { time(NULL) });

	/*
	struct tm {
   int tm_sec;         // seconds,  range 0 to 59
   int tm_min;         // minutes, range 0 to 59
   int tm_hour;        // hours, range 0 to 23
   int tm_mday;        // day of the month, range 1 to 31
   int tm_mon;         // month, range 0 to 11
   int tm_year;        // The number of years since 1900
   int tm_wday;        // day of the week, range 0 to 6
   int tm_yday;        // day in the year, range 0 to 365
   int tm_isdst;       // daylight saving time
};
	*/


	/*
	cout << "mktime(struct tm) : " << mktime(timeStruct) << endl;
	*/


	char timeStr[26];//at least 26 bytes!
	asctime_s(timeStr, 26, timeStruct);
	cout << "asctime(struct tm) : " << timeStr << endl;




	cout << "timeStruct.tm_hour  : " << timeStruct->tm_hour << endl;
	cout << "timeStruct.tm_min   : " << timeStruct->tm_min << endl;
	cout << "timeStruct.tm_sec   : " << timeStruct->tm_sec << endl;
	cout << "timeStruct.tm_mday  : " << timeStruct->tm_mday << endl;
	cout << "timeStruct.tm_wday  : " << timeStruct->tm_wday << endl;
	cout << "timeStruct.tm_yday  : " << timeStruct->tm_yday << endl;
	cout << "timeStruct.tm_year  : " << timeStruct->tm_year + 1900 << endl;
	cout << "timeStruct.tm_mon  : " << timeStruct->tm_mon << endl;
	cout << "timeStruct.tm_isdst : " << timeStruct->tm_isdst << endl;







	delete timeStruct;
	//------------------------------


	cout << "###################################" << endl;


	//------------------------------
	srand(time(0));
	int n = 50;
	int size = 15;
	cout << "Random numbers (using time() = milliseconds from Jan 1970 as a seed):" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << (rand() % n);

		if (!((i + 1) % 5) == 0)
		{
			cout << ", ";
		}
		else
		{
			cout << endl;
		}
	}
	//------------------------------


	cout << "###################################" << endl;


	//------------------------------

	cout << "run time of a function that loops alot (using time) : " << endl;

	//prototype
	void foo();

	time_t tBefore = -1, tAfter = -1;

	time(&tBefore);
	foo();
	time(&tAfter);

	cout << "runtime in seconds : " << (tAfter-tBefore) << endl;

	//------------------------------

	cout << "###################################" << endl;

	cout << "\n# MAIN DONE #\n" << endl;
	return 0;
}//main


void foo()
{
	long size = 10000000000;
	int s = 1;
	for (long i = 1; i <size ; i++)
	{
		s *=i;
	}
}












