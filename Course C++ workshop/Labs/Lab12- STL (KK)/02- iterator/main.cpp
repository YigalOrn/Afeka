#include <iostream>
using namespace std;
 
#include <list>
#include <vector>
 
/* 
T should have the following:
const_iterator, methods 'begin‘ and ‘end, operator<<
 */
template <class T>
void printCollection(const T& collection)
{
	T::const_iterator itr    = collection.begin();
	T::const_iterator itrEnd = collection.end();
 
	if (itr == itrEnd)
	{
		cout << "Collection is empty!\n";
		return;
	}
	for ( ; itr != itrEnd ; ++itr)
		cout << *itr << " ";
	cout << endl;
}

void printVector(const vector<int>& collection)
{
	vector<int>::const_iterator itr    = collection.begin();
	vector<int>::const_iterator itrEnd = collection.end();
 
	if (itr == itrEnd)
	{
		cout << "Collection is empty!\n";
		return;
	}
	for ( ; itr != itrEnd ; ++itr)
		cout << *itr << " ";
	cout << endl;
}

void printVector(vector<int>& collection)
{
	vector<int>::iterator itr    = collection.begin();
	vector<int>::iterator itrEnd = collection.end();
 
	if (itr == itrEnd)
	{
		cout << "Collection is empty!\n";
		return;
	}

	for ( ; itr != itrEnd ; ++itr)
		cout << *itr << " ";
	cout << endl;
}

void main()
{
	list<int> numbers;
	
	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_front(3);

	list<int>::iterator itr = numbers.begin();
	++itr;
	numbers.insert(itr, 4);

	numbers.insert(--numbers.end(), 5);
	printCollection(numbers);

	++itr;
	numbers.erase(itr);
	printCollection(numbers);

	numbers.erase(itr); // crashes!
	printCollection(numbers);

	system("pause");

}
