#include <iostream>
using namespace std;

#include <map>


template <class K, class V, class C>
void printCollection(const multimap<K, V, C>& collection)
{
	multimap<K, V, C>::const_iterator itr = collection.begin();
	multimap<K, V, C>::const_iterator itrEnd = collection.end();

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



void main()
{
	multimap<char*, char*, ltstr> phones;


	phones.insert(multimap<char*, char*, ltstr>::value_type("gogo", "1"));
	phones.insert(pair<char*, char*>("gogo", "1"));
	phones.insert(pair<char*, char*>("yoyo", "052-8529632"));
	phones.insert(pair<char*, char*>("momo", "054-8866553"));
	phones.insert(pair<char*, char*>("gogo", "22"));
	phones.insert(pair<char*, char*>("gogo", "333"));
	phones.insert(pair<char*, char*>("koko", "050-7534218"));

	printCollection(phones);
	
	cout << "\ngogo has " << phones.count("gogo") << " numbers\n";
	cout << "total records in phones: " << phones.size() << "\n\n";


	multimap<char*, char*, ltstr>::iterator found = phones.find("gogo");
	phones.erase(found); // deletes only the first value...
	
	cout << "after erase \"gogo\" : "<< endl;
	printCollection(phones);

	cout << "gogo has " << phones.count("gogo") << " numbers\n";
	cout << "total recors in phones: " << phones.size() << endl;


	system("PAUSE");

}
