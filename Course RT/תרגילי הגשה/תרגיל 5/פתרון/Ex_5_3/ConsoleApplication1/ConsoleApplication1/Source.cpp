#include <iostream>
using namespace std;

//#define DEBUG


//PF stands for pointer functions
typedef void(*PF)();

//an array of addresses for tasks/jobs. cyclic array.
static const int ntasks = 100;
static PF Task_Que[ntasks];

//queuer and dispatcher params
static PF *IN_PTR = NULL, *OUT_PTR = NULL;


//prototypes
void init_TaskQ(void);
void add2TaskQ(PF task);
void scan_TaskQ(void);

//tasks
void f1();
void f2();
void f3();
void f4();
void f5();




int main()
{
	int arr[100] = { 0 };
	for (int i = 0; i < 100; i++)
	{
		//cout << "i " << i << " : " << arr[i] << endl;
	}

	int *ptr = arr;
	for (int i = 0; i < 99; i++)
	{
		//cout << "i " << i << " : " << *ptr << endl;
		ptr++;
	}

	cout << ptr << endl;
	cout << &arr[100-1] << endl; //arr[100] = *(arr+100)

/*
	void myCheck(void);

	init_TaskQ();

	add2TaskQ(&f1);
	add2TaskQ(&f2);
	add2TaskQ(&f3);
	add2TaskQ(&f4);
	add2TaskQ(&f5);

	scan_TaskQ();

#ifdef DEBUG
	myCheck();
#endif
*/


	return 0;
}//main

void myCheck(void)
{
	for (int i = 0; i < 300; i++)
	{
		cout << "--------------------------------------" << endl;
		cout << "MyCheck iteration : " << i + 2 << endl;

		add2TaskQ(&f1);
		add2TaskQ(&f2);
		add2TaskQ(&f3);
		add2TaskQ(&f4);
		add2TaskQ(&f5);

		scan_TaskQ();
		cout << "--------------------------------------" << endl;
	}
}

void init_TaskQ(void)
{
	//init dispatcher and queuer params
	OUT_PTR = IN_PTR = &Task_Que[0];
}

void add2TaskQ(PF task)
{
	//add a new task to Task_Que
	*IN_PTR = task;

	//increment ptr
	IN_PTR++;

#ifdef DEBUG
	static int ptrIncrementCtr = 0;//debug
	ptrIncrementCtr++;//debug
#endif


	//check if in array bounds, cyclic
	if (IN_PTR == &Task_Que[ntasks])
	{
		IN_PTR = &Task_Que[0];

#ifdef DEBUG
		ptrIncrementCtr = 0;//debug
#endif

	}

	//check dispatcher and queuer params, check if queue is full
	if (IN_PTR == OUT_PTR)
	{
		exit(1);//exit with 1 for error
	}

#ifdef DEBUG
	cout << "$ IN_PTR points to index: " << ptrIncrementCtr << endl;
#endif

}

void scan_TaskQ(void)
{

	while (OUT_PTR != IN_PTR)
	{
		(*OUT_PTR)();
		OUT_PTR++;

#ifdef DEBUG
		static int ptrIncrementCtr = 0;//debug
		ptrIncrementCtr++;//debug
#endif

		/*
		please notice that Task_Que[ntasks] is o.k why? ,
		because it is the same as :
		ptr = Task_Que

		ptr = ptr+ntasks;

		pointer arithmetics...

		if i wanted to get something from the array i.e. the value this would fail
		but i only need the address...
		*/
		if (OUT_PTR == &Task_Que[ntasks])
		{
			OUT_PTR = &Task_Que[0];

#ifdef DEBUG
			ptrIncrementCtr = 0;//debug
#endif

		}

#ifdef DEBUG
		cout << "$ OUT_PTR points to index: " << ptrIncrementCtr << endl;
#endif

	}


	//empty queue
	cout << "# queue is empty #" << endl;
}

void f1()
{
	cout << "1" << endl;
}

void f2()
{
	cout << "2" << endl;
}

void f3()
{
	cout << "3" << endl;
}

void f4()
{
	cout << "4" << endl;
}

void f5()
{
	cout << "5" << endl;
}















