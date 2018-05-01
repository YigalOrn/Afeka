/*
T should support:

operator=
def c'tor

*/

#ifndef __ITERATOR_H
#define __ITERATOR_H

#include <iostream>
using namespace std;

template <class T>
class Array
{

//get iterator type with the container outside the class
public:
	class iterator
	{

	public:
		
		iterator(Array& arr, int i) : arr(&arr), i(i) 
		{
		}

		bool operator==(const iterator& other) const 
		{
			return (arr == other.arr && i == other.i); 
		}

		bool operator!=(const iterator& other) const 
		{ 
			return !(*this == other); 
		}

		//dereference the curr iterator, const ver 
		const T& operator*() const 
		{ 
			return arr->arr[i]; 
		}

		T& operator*() 
		{ 
			return arr->arr[i]; 
		}

		//prefix
		iterator& operator++()
		{
			i++;
			return *this;
		}

		//postfix, using dummy int = 0
		iterator operator++(int dummyInt)
		{
			iterator temp(*this);//use def copy-c'tor
			i++;
			return temp;
		}

		//prefix
		iterator& operator--()
		{
			i--;
			return *this;
		}

		//postfix
		iterator operator--(int)
		{
			iterator temp(*this);
			i--;
			return temp;
		}

	private:
		Array* arr;//ref to the template container
		int i;
	};



	//-----------------------------------------------------


	Array(int size = 7) : logicalSize(0), phisicalSize(size)
	{
		arr = new T[phisicalSize];
	}

	Array(const Array& other) : arr(NULL)
	{
		*this = other;
	}

	~Array() 
	{
		delete []arr; 
	}

	const Array& operator=(const Array& other)
	{
		if (this != &other)//optimization
		{
			logicalSize = other.logicalSize;
			phisicalSize = other.phisicalSize;
			delete []arr;
			arr = new T[phisicalSize];
			for (int i = 0; i < logicalSize; i++)
			{
				arr[i] = other.arr[i];
			}
		}
		return *this;
	}

	const T& operator[](int i) const
	{ 
		return arr[i]; 
	}

	T& operator[](int i) 
	{
		return arr[i];
	}

	void push_back(const T& value)
	{
		if (logicalSize == phisicalSize)
		{
			resize();//multiply by 2
		}
		arr[logicalSize++] = value;
	}


	const T& front()    const 
	{ 
		return arr[0]; 
	}
	
	int      size()     const 
	{ 
		return logicalSize; 
	}
	
	int      capacity() const 
	{ 
		return phisicalSize;
	}
	
	bool     empty()    const 
	{ 
		return logicalSize == 0; 
	}
	
	void     clear() 
	{ 
		logicalSize = 0; 
	}

	void insert(iterator& pos, const T& val)
	{
		if (logicalSize == phisicalSize)
		{
			resize();
		}

		//-------------------------
		//moves each element in the collection by one place farther, including current value of pos!!
		iterator itrEnd = end();
		//cout << "crushes here if the copy ctor is not good" << endl;
		iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
		while (itrCurrent != pos)
		{
			*itrCurrent = *itrPrev;
			itrCurrent = itrPrev--;//postfix: first gives the old position ! and then decrements
		}
		//-------------------------

		*pos = val;
		//don't be confused by the fact that pos 
		//is of a reference type in this function argument list !
		//this the pointer syntax of an object of type iterator !!

		logicalSize++;
	}

	/*
	//not supported
	const iterator&  erase
		(const iterator& first, const iterator& last);
   */


	iterator begin() 
	{ 
		return iterator(*this, 0); 
	}
	
	iterator end() 
	{ 
		return iterator(*this, logicalSize); 
	}
	
	/*
	//use ostream obj
	void print() const
	{
		for (int i = 0; i < logicalSize; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	*/



private:

	void resize()
	{
		phisicalSize *= 2;
		T* temp = new T[phisicalSize];
		for (int i = 0; i < logicalSize; i++)
		{
			temp[i] = arr[i];
		}

		delete[]arr;
		arr = temp;//temp was dynamically allocated
	}

	T* arr;
	int logicalSize;
	int phisicalSize;


};//class Array

#endif//__ITERATOR_H