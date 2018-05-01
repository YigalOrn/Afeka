#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;



template<class T>
class Print
{
public:
	void operator()(const T& val) const
	{
		cout << val << " ";
	}
};


class Inc
{
public:
	template<class T>
	void operator()(T& val) const
	{
		val++;
	}
};

//template<class Iterator, class Function>//same, only a place holder, a name!
//template<class iterator, class Function>//same
template<class T, class F>//same
void applyAll(T begin, T end, const F& f)
{
	for (; begin != end; ++begin)
		f(*begin);
}



template<class T>
void mySwap(T& num1, T& num2)
{
	T temp = num1;
	num1 = num2;
	num2 = temp;
}

template<class T, class Comparator>
void sort(T arr[], int size, const Comparator& compare)
{
	for (int i = size - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (compare(arr[j], arr[j + 1]) < 0)
			{
				mySwap(arr[j], arr[j + 1]);
			}
		}
	}
}

int compareNumbers(int n1, int n2)
{
	if (n1 < n2) return 1;
	else if (n1 > n2) return -1;
	else return 0;
}

void main()
{
	ostream_iterator<int> output(cout, " ");

	int arr[] = { 3,2,7,1,9,4 };
	sort(arr, sizeof(arr) / sizeof(arr[0]), compareNumbers);
	copy(arr, arr + sizeof(arr) / sizeof(arr[0]), output);
	cout << endl;


	sort(arr, sizeof(arr) / sizeof(arr[0]), [](int n1, int n2)
	{
		if (n1 < n2) return -1;
		else if (n1 > n2) return 1;
		else return 0;
	});
	copy(arr, arr + sizeof(arr) / sizeof(arr[0]), output);
	cout << endl;




	system("pause");
}//main




/*
void main()
{
	vector<int> numbers;

	for (int i = 1; i < 10; i += 2)
		numbers.push_back(i);//1, 3, 5, 7, 9


	//explicit calls of direct-initialization and not copy initialization
	Print<int> p1 = Print<int>{};
	Print<int> p2{};

	//applyAll(numbers.begin(), numbers.end(), p2);
	cout << endl;

	//applyAll(numbers.begin(), numbers.end(), Print<int>{});
	cout << endl;

	applyAll(numbers.begin(), numbers.end(), Inc());
	cout << endl;

	applyAll(numbers.begin(), numbers.end(), [](int x1){cout << x1 << " ";});
	cout << endl;

	system("pause");

}//main

*/


