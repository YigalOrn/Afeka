#include <iostream>
using namespace std;


template<class ELEMENT> class Array
{
	class Element
	{
		Array<ELEMENT>* pArray;
		int index;
	public:
		Element(Array<ELEMENT>* p, int i)
			: pArray(p), index(i) {}
		const Element& operator=(const ELEMENT& e) {
			pArray->set(index, e); // call copy-on-write
			return *this;

		}
		operator ELEMENT()const {
			return pArray->arr[index];

		}
	};

	friend class Element;
	ELEMENT* arr;
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
	void set(int index, const ELEMENT& e) {
		if (*ref_counter > 1) { // need copy-on-write!
			Array temp = clone();
			detach();
			attach(temp);

		}
		arr[index] = e;

	}
public:
	explicit Array(int);


	Array<ELEMENT> clone()const;
	Array(const Array<ELEMENT>& a) { attach(a); }
	~Array() { detach(); }
	const Array& operator=(const Array<ELEMENT>& a) {
		detach(); attach(a); return *this;

	}
	Element operator[](int index) {
		return Element(this, index);

	}
	const ELEMENT& operator[](int index)const {
		return arr[index];

	}
};

template<class ELEMENT>
Array<ELEMENT>::Array(int size1)
	: size(size1), ref_counter(new int(1))
{
	arr = new ELEMENT[size];
}

template<class ELEMENT>
Array<ELEMENT> Array<ELEMENT>::clone()const {
	Array temp(size);
	for (int i = 0; i < size; ++i) {
		temp.arr[i] = arr[i];

	}
	return temp;

}

int main()
{
	Array<int> a1(1), a2(2);
	Array<int>* ptr3 = new Array<int>(3);
	a2[0] = 1;
	a2[1] = 2;
	a1 = a2;
	(*ptr3)[0] = a1[0] + a2[1];
	(*ptr3)[1] = a1[1] + a2[0];
	cout << (*ptr3)[0] << ", " << (*ptr3)[1] << endl;
	delete ptr3;
	return 1;
}