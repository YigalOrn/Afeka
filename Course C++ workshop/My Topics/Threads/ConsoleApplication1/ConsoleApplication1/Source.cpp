// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
using namespace std;

#include <cstdio>

void foo(char ch, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%3c", ch);
		if ((i + 1) % 5 == 0)
		{
			printf("\n");
		}
	}
}


int main()
{
	thread thr1(foo, 'A', 50);

	thread thr2(foo, 'Q', 30);

	thread *thr3 = new thread(foo, '*', 100);

	thr1.join();
	thr2.join();
	thr3->join();

	cout << endl << "# MAIN-DOEN #" << endl;
	return 0;
}//main