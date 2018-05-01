
/*
https://msdn.microsoft.com/en-us/library/f1b2td24.aspx

*/


/*

Map:



*/

#ifndef __Map_h
#define __Map_h

#include <iostream>
using namespace std;

#include "Pair.h"




template<class K, class V>
class Map
{

	template<class K, class V>
	friend ostream& operator<<(ostream& os, const Map<K, V>& map);

	/*
	friend ostream& operator<<(ostream& os, const Map<K, V>& map)
	{
		os << "Map [ ";

		int currSize = map.getCurrSize();
		char delimeter = map.getDelimeter();

		for (int i = 0; i < currSize; i++)
		{
			os << map.arr[i]/Pair object/ << delimeter;
		}

		os << " ]";

		return os;
	}

*/

public:

	Map(int s = Map::MaxSize, char delimeter = ' ')throw(char*);
	~Map();


	inline int getSize()const;
	inline int getCurrSize() const;
	inline char getDelimeter() const;

	V& operator[](K key) throw(char*);

private:

	int checkIfKeyInMap(K key);


	static const int MaxSize = 10;

	Pair<K, V>* arr;
	int currSize;
	int size;
	char delimeter;


};//class Map





template<class K, class V>
Map<K, V>::Map(int s, char delimeter) throw(char*) :delimeter(delimeter), size(s)
{
	if (size > Map::MaxSize)
	{
		throw "Size exceeded Max Size";
	}
	else
	{
		/*
		create a static array i.e. has s already existing Pairs all with
		garbage values created by the default c'tor
		*/
		arr = new Pair<K, V>[size];
	}
}

template<class K, class V>
Map<K, V>::~Map()
{
	delete[]arr;//it is a static array not array of pointers!
}

template<class K, class V>
int Map<K, V>::getSize()const
{
	return size;
}

template<class K, class V>
int Map<K, V>::getCurrSize() const
{
	return currSize;
}

template<class K, class V>
char Map<K, V>::getDelimeter() const
{
	return delimeter;
}

template<class K, class V>
int Map<K, V>::checkIfKeyInMap(K key)
{
	int i;
	Pair<K, V>* temp = 0;

	for (i = 0, temp = arr; i < getCurrSize();i++, temp++)
	{
		if (temp->getKey() == key)
		{
			return i;
		}
	}//for

	return (i*-1);

}

template<class K, class V>
V& Map<K, V>::operator[](K key) throw(char*)
{
	int index = checkIfKeyInMap(key);

	if (index > 0)
	{
		//key is in this map
		return (this->arr[index]).getValue();
	}
	else
	{
		//key isn't in this map
		if (getCurrSize() < getSize())
		{
			arr[currSize].setKey(key);
			return arr[currSize++].getValue();
		}
		else
		{
			throw "can't add more element to this map";
		}
	}
}



template<class K, class V>
ostream& operator<<(ostream& os, const Map<K, V>& map)
{
	os << "Map [ ";

	int currSize = map.getCurrSize();
	char delimeter = map.getDelimeter();

	for (int i = 0; i < currSize; i++)
	{
		os << map.arr[i] /*Pair object*/ << delimeter;
	}

	os << " ]";

	return os;
}




#endif//__Map_h




