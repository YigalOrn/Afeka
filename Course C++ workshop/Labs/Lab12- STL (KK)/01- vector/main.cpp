#include <iostream>
using namespace std;

#include <vector>




/*
class Person
{
	char name[10];
public:
	Person(const char* name)
	{
		setName(name);
	}
	void setName(const char* name)
	{
		strcpy(this->name, name);
	}
};

void main()
{
	vector<Person> persons;
	vector<Person*> personsPtr;

	Person p1("gogo"), p2("momo");

	persons.push_back(p1);
	persons.push_back(p2);

	personsPtr.push_back(&p1);
	personsPtr.push_back(&p2);

	p1.setName("gogogo");
}

*/





void main()
{
	vector<int> numbers;  // --> Collection is empty!

	numbers.reserve(0);
	numbers.push_back(55);
	
	cout << "max_size " << numbers.max_size() << endl;

	cout << "Is collection empty? " << numbers.empty() << endl; // --> 1
	cout << "size=" << numbers.size() << " capacity=" 
		<< numbers.capacity() << endl;         // --> size=0 capacity=0

	numbers.push_back(4);
	cout << "size=" << numbers.size() << " capacity=" 
		<< numbers.capacity() << endl;        // --> size=1 capacity=1

	numbers.push_back(8);
	numbers.push_back(2);
	cout << "size=" << numbers.size() << " capacity=" 
		<< numbers.capacity() << endl;        // --> size=3 capacity=3

	cout << "Is collection empty? " << numbers.empty() << endl; // --> 0
	cout << "size=" << numbers.size() << " capacity=" 
		<< numbers.capacity() << endl;         // --> size=3 capacity=3
	// values in the vector: 4 8 2 3
	int firstValue = numbers.front();
	cout << "first value is " << firstValue << endl; 
	// --> first value is 4, values in the vector: 4 8 2

	numbers.pop_back(); // values in the vector: 4 8 2
	cout << "size=" << numbers.size() << " capacity=" 
		<< numbers.capacity() << endl;     // --> size=3 capacity=4

	numbers.reserve(10); 
	cout << "size=" << numbers.size() << " capacity=" 
		<< numbers.capacity() << endl;     // --> size=3 capacity=4

	numbers.clear();
	cout << "size=" << numbers.size() << " capacity=" 
		<< numbers.capacity() << endl;     // --> size=0 capacity=4


	system("pause");

}





