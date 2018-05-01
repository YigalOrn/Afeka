#include <iostream>
using namespace std;

template <class E> class Array
{
	class Element
	{
		Array<E>* const pArray; // pointer can't move
		const int index;
	public:
		Element(Array<E>* p, int i)
			:pArray(p), index(i) {}
		const Element& operator=(const E& e) {
			pArray->set(index, e); // call copy-on-write
			return *this;
		}
		operator E() const {
			return pArray->arr[index];
		}

		E myFixMethod() const
		{
			return pArray->arr[index];
		}
	};//Element

	friend class Element;
	E* arr;
	int size;
	int* ref_counter;
	void attach(const Array& a) {
		arr = a.arr; size = a.size;
		ref_counter = a.ref_counter;
		++(*ref_counter);
	}
	void detach() {
		if (--(*ref_counter) == 0) {
			delete[]arr;
			delete ref_counter;
		}
	}
	void set(int index, const E& e) {
		if (*ref_counter > 1) { // need copy-on-write
			Array temp = clone();
			detach();
			attach(temp);
		}
		arr[index] = e;
	}
public:
	explicit Array(int);
	Array<E> clone() const;
	Array(const Array<E>& a) { attach(a); }
	~Array() { detach(); }
	const Array& operator=(const Array<E>& a) {
		detach(); attach(a); return *this;
	}
	Element operator[](int index) {
		return Element(this, index);
	}
	const E& operator[](int index) const {
		return arr[index];
	}
};//Array

template<class E>
Array<E>::Array(int size1)
	:size(size1), ref_counter(new int(1))
{
	arr = new E[size];
}

template<class E>
Array<E> Array<E>::clone() const {
	Array temp(size);
	for (int i = 0; i < size; ++i)
	{
		temp.arr[i] = arr[i];
	}
	return temp;
}

int main()
{
	Array<int> intArr1(5), intArr2(6);

	intArr1[0] = (int)(intArr2[0] = 1);


	return 0;
}//main









