#ifndef __Set
#define __Set


class Set
{
	static int serial;

	int id;
	int currSize;
	int maxSize;
	int *array;
	
	bool checkIfInSet(const int& newVal) const;

public:

	/*def c'tor*/
	Set(int  maxSize = 1000);//overloaded default, default values in .h 
	/*copy c'tor*/
	Set(const Set &other);
	/*d'tor*/
	~Set();

	void showSet() const;
	bool add(const int newVal);
	inline int getCurrentSize(){ return currSize; }

	/*Overloading Operators*/

	//2)
	const Set& operator=(const Set& other);

	//3)
	friend Set operator+(const int& param, const Set& set);
	friend Set operator+(const Set& set, const int& param);

	//4) union
	Set operator+(const Set& other) const;

	//5)
	Set operator+=(int param);

	//6)
	friend ostream& operator<<(ostream&, const Set&);

	//7)
	bool operator>(const Set& other) const;

	//8)
	int& operator[](const int index) const ;

};


#endif