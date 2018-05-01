#include <iostream>
#include <set>
using namespace std;

/*
T should have the following:
const_iterator, methods 'begin‘ and ‘end, operator<<
*/
template <class T>
void printCollection(const T& collection)
{
	T::const_iterator itr = collection.begin();
	T::const_iterator itrEnd = collection.end();

	if (itr == itrEnd)
	{
		cout << "Collection is empty!\n";
		return;
	}
	for (; itr != itrEnd; ++itr)
		cout << *itr << " ";
	cout << endl;
}

class MySortPredicate
{
public:
	bool operator()(const int& n1, const int& n2) const
	{
		if (n1 <= n2)return true;
		else return false;
	}
};

class ltstr
{
public:
	bool operator()(const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) < 0;
	}
};

/*
const int SIZE = 5;
typedef char* StrMat[SIZE];
StrMat strMat = { "aaaa", "bbbb", "cccc", "dddd", "eeee" };
*/

void main()
{

	set < int, MySortPredicate> intSet;
	//set < int > intSet;

	intSet.insert(4);
	intSet.insert(2);
	intSet.insert(1);
	intSet.insert(3);
	intSet.insert(1);

	printCollection(intSet);

	cout << "Is set empty? " << intSet.empty() << endl;
	cout << "Value 1 appears " << intSet.count(1) << " times\n";

	cout << "Value 8 appears " << intSet.count(8) << " times\n";

	intSet.erase(2);
	printCollection(intSet);
	cout << "There are " << intSet.size() << " values in the set\n";


	cout << "There can be max " << intSet.max_size() << " elements\n";


	set<int>::iterator itr = intSet.find(4);
	if (itr != intSet.end())
		cout << "4 is found\n"; // 4 is found

	intSet.clear();
	printCollection(intSet);


}





/*
void main()
{

	char* words[] = { "shalom", "kita", "alef", "shalom", "kita", "beit" };
	//set<char*> wordsSet;
	set<const char*> wordsSet;

	int numOfWords = sizeof(words) / sizeof(words[0]);
	for (int i = 0; i < numOfWords; i++)
		wordsSet.insert(words[i]);

	printf("The words in the set:\n");
	printCollection(wordsSet);

	wordsSet.clear();
	printf("The words in the set after clear:\n");
	printCollection(wordsSet);

}
*/



/*
int main()
{
	const int SIZE = 6;
	char* words[SIZE] = { "shalom", "kita", "alef", "shalom", "kita", "beit" };
	int numOfWords = sizeof(words) / sizeof(words[0]);

	set<char*, ltstr> wordsSet;

	
	//for (int i = 0; i < numOfWords; i++)
	//	wordsSet.insert(words[i]);


	wordsSet.insert(words, words + SIZE);


	printf("The words in the set:\n");
	printCollection(wordsSet); // alef beit kita shalom
}
*/





