/*

Pair:
- supports =

K:
- supports =
- supports ==

V:
- supports =



*/


#ifndef __Pair_h
#define __Pair_h


#include <iostream>
using namespace std;


template<class K, class V>
class Pair
{

	friend ostream& operator<<(ostream& os, Pair& pair)
	{
		os << "(" << pair.getKey() << ", " << pair.getValue() << ")";
		return os;
	}


public:

	Pair();//for arrays
	Pair(K t, V q);
	

	void setKey(K key);
	void setValue(V value);

	 K& getKey();
	 V& getValue();


private:

	K key;
	V value;

};//class Pair


template<class K, class V>
Pair<K, V>::Pair()
{
	/*default c'tor*/
}

template<class K, class V>
Pair<K, V>::Pair(K t, V q)
{
	setKey(key);
	setValue(value);
}

template<class K, class V>
void Pair<K, V>::setKey(K key)
{
	this->key = key;
}

template<class K, class V>
void Pair<K, V>::setValue(V value)
{
	this->value = value;
}


template<class K, class V>
 K& Pair<K, V>::getKey() 
{
	return key;
}

template<class K, class V>
 V& Pair<K, V>::getValue()
{
	return value;
}



#endif//__Pair_h