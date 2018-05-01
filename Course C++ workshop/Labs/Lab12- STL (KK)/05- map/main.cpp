#include <iostream>
#include <map>
using namespace std;

template <class K, class V, class C>
void printCollection(const map<K, V, C>& collection)
{
	map<K, V, C>::const_iterator itr = collection.begin();
	map<K, V, C>::const_iterator itrEnd = collection.end();

	if (itr == itrEnd)
	{
		cout << "Collection is empty!\n";
		return;
	}

	for (; itr != itrEnd; ++itr)
		cout << itr->first << " \t" << itr->second << endl;
	cout << endl;
}

class ltstr
{
public:
	bool operator()(const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) < 0;
	}
};

int main()
{
	map<char*, char*, ltstr> phones;
	
	//typedef map<char*, char*, ltstr> mcccc; // mcccc : map const char* const char*
	//mcccc phones;

	phones["gogo"] = "050-5566778";
	phones["yoyo"] = "052-8529632";
	phones["momo"] = "054-8866553";
	phones["gogo"] = "050-5555555"; // instead the previous value
	phones["koko"] = "050-7534218";

	
	//phones["koko"] = "999";//gets a value ref and changes it, this is not an insertion action!
	phones.insert(map<char*, char*, ltstr>::value_type("koko", "111"));//dupe key is ignored


	//printCollection(phones);


	for (map<char*, char*, ltstr>::const_iterator itr = phones.begin(); itr != phones.end();++itr)
	{
		cout << "(" << itr->first << ", " << itr->second << ")" << endl;
	}
	cout << endl;

	
	printCollection(phones);

	system("pause");

}

