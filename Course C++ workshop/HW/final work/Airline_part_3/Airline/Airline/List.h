#ifndef __List_H
#define __List_H

#include <iostream>
#include <cstring>
using namespace std;

#include "ListNode.h"

template<class T>
class List
{

public:
	List();
	~List();
	void insertAfterTail(const T& newData);
	void remove(T& dataToDelete);
	void print(ostream& out) const;

	bool isEmpty() const;
	T& isElementOfList(const T& dataToCheck) throw (const string&);
private:
	ListNode<T>* head;
	ListNode<T>* tail;
	ListNode<T>* getNewNode(const T& newData);
};

// implementation

template<class T>
List<T>::List() 
	: head(0), tail(0)
{
}

template<class T>
List<T>::~List()
{
	if (!isEmpty())
	{
		ListNode<T>* currentPtr = head;
		ListNode<T>* delPtr; // previous node

		while (currentPtr != 0)
		{
			delPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
			delete delPtr;
		}
	}
}

template<class T>
void List<T>::insertAfterTail(const T& newData)
{
	ListNode<T> *newPtr = getNewNode(newData); // new node

	if (isEmpty())
	{
		head = tail = newPtr;
	}
	else
	{
		tail->nextPtr = newPtr;
		tail = newPtr;
	}
}

template<class T>
void List<T>::remove(T& dataToDelete)
{
	ListNode *ptrPre = 0, *ptrDel = 0;
	
	if (isEmpty())
	{
		return;
	}

	if (head->data == dataToDelete)
	{
		ptrDel = head;
		head = ptrDel->nextPtr;
		if (!head)
		{
			tail = head;
			//notice tail might be garbage when there is one node left, but head says the list is empty!
		}
		delete ptrDel;
		return;
	}

	ptrPre = head;
	ptrDel = head->nextPtr;
	while (ptrDel)
	{
		if (ptrDel->data == dataToDelete)
		{
			ptrPre->nextPtr = ptrDel->nextPtr;
			if (ptrDel == tail)
			{
				tail = ptrPre;
			}
			delete ptrDel;
			break;
		}
		ptrPre = ptrDel;
		ptrDel = ptrDel->nextPtr;
	}
	
	return;
}

template<class T>
bool List<T>::isEmpty() const
{
	return head == 0;
}

template<class T>
T& List<T>::isElementOfList(const T& dataToCheck) throw (const string&)
{
	string msg("No such element in the list, element type: ");
	msg.append(typeid(T).name() + 6);
	if (isEmpty())
	{
		throw msg;
	}

	ListNode<T> *currentPtr = head;
	while (currentPtr)
	{
		if (currentPtr->data == dataToCheck)
		{
			return currentPtr->data;
		}
		currentPtr = currentPtr->nextPtr;
	}

	throw msg;
	return head->data;  // never reaches this line
}

template<class T>
ListNode<T> *List<T>::getNewNode(const T &value)
{
	return new ListNode<T>(value);
}

template<class T>
void List<T>::print(ostream& out) const
{
	if (isEmpty())
	{
		return;
	}
	
	ListNode<T> *currentPtr = head;
	while (currentPtr)
	{
		out << currentPtr->data << endl;
		currentPtr = currentPtr->nextPtr;
	}
}

#endif //__List_H

