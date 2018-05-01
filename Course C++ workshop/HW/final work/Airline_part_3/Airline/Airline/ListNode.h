/*
T - requires copy c'tor
T - requires operator==
T - requires operator<<
*/

#ifndef __ListNode_H
#define __ListNode_H

template<class T> class List;// forward declaration

template<class T>
class ListNode
{
	friend class List<T>;//to use private members

public:
	ListNode(const T &);
	T getData() const;// notice requires copy c'tor
private:
	T data;
	ListNode<T> *nextPtr;
};


// implementation

template<class T>
ListNode<T>::ListNode(const T &newData)
	: data(newData), nextPtr(0)
{
} 

template<class T>
T ListNode<T>::getData() const
{
	return data;
}

#endif // __ListNode_H
