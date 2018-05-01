#include <iostream>
using namespace std;



void bubbleSort(int arr[], int size);

void main()
{
	//prototypes
	void q1(int& a1, int& a2, int& a3);
	int& q2(int& a1, int& a2);


	

	/*
	int a1, a2, a3;
	cout << "Enter 3 int numbers : \n";
	cin >> a1 >> a2 >> a3;
	q1(a1, a2, a3);
	cout << "The result of q1 is : " << a1 << ", " << a2 << ", " << a3 << "\n";
	*/

	int a1 = 9, a2 = 19;
	int& refMax = q2(a1, a2);

	cout << "refMax = " << refMax << "\n";

}


int& q2(int& a1, int& a2)
{
	if (a1 > a2)return a1;
	else return a2;
}


void q1(int& a1, int& a2, int& a3)
{

	int arr[3] = { a1, a2, a3 };

	bubbleSort(arr, sizeof(arr) / sizeof(arr[0]));

	a1 = arr[2];
	a2 = arr[1];
	a3 = arr[0];


}//q1

void bubbleSort(int arr[], int size)
{
	bool changed = false;

	for (int i = size - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			int temp;
			if (arr[j]>arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;

				changed = true;
			}


		}//for_j

		if (changed == false)
		{
			break;
		}
	}//for_i


}//bubbleSort







