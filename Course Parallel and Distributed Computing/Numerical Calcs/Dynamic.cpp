#include <mpi.h>

#include <iostream>
#include <iomanip>//for precision print
#include <time.h>//notice c++ has all rand needs except the time seed
#include <cmath>//for atan, showing pi by c++ lib
using namespace std;


#include "DynamicPrototypes.h"


int main(int argc, char *argv[])
{
	int numprocs;
	int myRank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	/*
	command line params are:
	sqaure edge size/len 
	or
	sqaure edge size/len, points per slave, tot points to check, num of slaves + root
	e.g. 2 500 20000 12
	*/
	if (argc != 2 && argc != 5)
	{
		cout << "# argc doesnt match #\n#\n params are:\n sqaure edge size.\n sqaure edge size, points per slave(task size), tot points to check, num of slaves + root. \n#" << endl;
		MPI_Abort(MPI_COMM_WORLD, 1);
	}


	int root = 0;
	//time parameters for mpi_wtime
	double t1, t2;
	double squareEdgeSize;
	//circle radius derived from squareEdgeSize
	double radius;

	//counts the points that are inside the circle
	int densityResult;
	//task size, if divided by 2 we get the points each slave gets
	int taskSize;
	int numOfTasks;
	int taskPoolSize;
	int currTaskPtr;
	double* taskPool = NULL;

	//radius and taskSize are packed and sent in bcast using this array
	const int initDataSize = sizeof(double) + sizeof(int);
	char initData[initDataSize];
	int initDataPos;

	double* pointsToCheck = NULL;


	if (myRank == root)
	{
		squareEdgeSize = atof(argv[1]);
		radius = squareEdgeSize / 2;


		masterInitData(
			argc, argv,
			&taskPool, taskPoolSize, numOfTasks, taskSize, numprocs, radius
			);


		initDataPos = 0;
		MPI_Pack(&radius, 1, MPI_DOUBLE, initData, initDataSize, &initDataPos, MPI_COMM_WORLD);
		MPI_Pack(&taskSize, 1, MPI_INT, initData, initDataSize, &initDataPos, MPI_COMM_WORLD);
	
		t1 = MPI_Wtime();
	}


	MPI_Bcast(initData, initDataSize, MPI_PACKED, root, MPI_COMM_WORLD);


	if (myRank != root)
	{
		//notice it is unnecessary for root to do this

		initDataPos = 0;
		MPI_Unpack(initData, initDataSize, &initDataPos, &radius, 1, MPI_DOUBLE, MPI_COMM_WORLD);
		MPI_Unpack(initData, initDataSize, &initDataPos, &taskSize, 1, MPI_INT, MPI_COMM_WORLD);

		pointsToCheck = new double[taskSize];
	}


	if (myRank == root)
	{
		//master loads tasks and then continues to listening
		currTaskPtr = 0;
		for (int i = 1; i < numprocs; i++)
		{
			MPI_Send(&taskPool[currTaskPtr], taskSize, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
			currTaskPtr += taskSize;
		}
		numOfTasks -= (numprocs - 1);

		masterDividesTasks(taskPool, numOfTasks, taskSize, currTaskPtr, densityResult);
		masterTerminatesTaskPool(numprocs, densityResult, radius);

		t2 = MPI_Wtime();

		masterPrintResult(densityResult, taskPoolSize, t1, t2);
	}
	else
	{
		MPI_Recv(
			pointsToCheck, taskSize, MPI_DOUBLE,
			root, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE
			);

		slaveRecDataAndWork(root, radius, pointsToCheck, taskSize);
	}


	MPI_Finalize();
	return 0;


}//main

void masterInitData(
	const int& argc, const char*const * argv,
	double** taskPoolPtr, int& taskPoolSize,
	int& numOfTasks, int& taskSize,
	const int& numprocs, double radius)
{
	double f;
	const double min = -radius, max = radius;

	srand(unsigned(time(NULL)));

	if (argc == 2)
	{
		do
		{
			numOfTasks = rand();
		} while (numOfTasks < numprocs *(rand() % 101));


		do
		{
			//omit % if you have more process power
			//even because x = [i] and y = [i+1]
			taskSize = rand() % 10001;
		} while (taskSize % 2 != 0);
	}
	else
	{
		if (numprocs != atoi(argv[4])) 
		{
			cout << "# numprocs doesn't match #" << endl;
			MPI_Abort(MPI_COMM_WORLD, 1);
		}
		
		/*
		points are sent in the following format:
		given an array the array will look like - [x1,y1,x2,y2,x3,y3,.......,xn,yn]
		that is why its size should be a multiple of 2.
		*/
		taskSize = atoi(argv[2]) * 2;
		numOfTasks = atoi(argv[3]) / atoi(argv[2]);
	}


	taskPoolSize = numOfTasks*taskSize;
	(*taskPoolPtr) = new double[taskPoolSize];

	for (int i = 0; i < taskPoolSize; i++)
	{
		//    0<= f <=1
		f = (double)rand() / RAND_MAX;
		(*taskPoolPtr)[i] = min + f*(max - min);
	}

}

void masterDividesTasks(double*& taskPool, int& numOfTasks, const int& taskSize,
	int& currTaskPtr, int& densityResult)
{
	int tempRes;
	MPI_Status status;

	densityResult = 0;

	//divide tasks to slaves that ask for them
	while (numOfTasks > 0)
	{
		MPI_Recv(
			&tempRes, 1, MPI_INT,
			MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,
			&status
			);

		//accumulate each slave local result
		densityResult += tempRes;

		MPI_Send(
			&taskPool[currTaskPtr], taskSize, MPI_DOUBLE,
			status.MPI_SOURCE, 0, MPI_COMM_WORLD
			);

		//adjust from where to get the next task to be asked and how many tasks are left
		numOfTasks--;
		currTaskPtr += taskSize;

	}//while
}

void masterTerminatesTaskPool(const int& numprocs, int& densityResult, const double& radius)
{
	double finVal = radius*radius + 1;//a point cant have this value
	int tempRes = 0;
	MPI_Status status;

	//announce to slave that the work is done
	for (int i = 1; i < numprocs; i++)
	{
		MPI_Recv(
			&tempRes, 1, MPI_INT,
			MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status
			);

		densityResult += tempRes;

		//used with finVal to tell the slave that he can terminate
		MPI_Send(
			&finVal, 1, MPI_DOUBLE,
			status.MPI_SOURCE, 0, MPI_COMM_WORLD
			);
	}//for
}

void masterPrintResult(const int& densityResult, const int& taskPoolSize,
	const double& t1, const double& t2)
{
	//master calculates pi using slaves joint result
	double pi = 4.0 * (densityResult / (taskPoolSize / 2.0));
	cout << "Time elapsed:\t" << (t2 - t1) << endl;
	cout << "PI by calculator is -\t\t3.141592654" << endl;
	cout << "PI by math function atan() -\t" << setprecision(10) << atan(1)*4.0 << endl;
	cout << "PI by approximation is -\t\t" << setprecision(10) << pi << endl;
}

void slaveRecDataAndWork(const int& root, const double& radius, double* pointsToCheck,
	const int& taskSize)
{

	double x, y;
	int myDensityResult = 0;
	double temp;
	const double circleEquationConstant = radius*radius;
	const double finVal = circleEquationConstant + 1;//a point cant have this value



	//work until master says otherwise
	do
	{
		//do work
		for (int i = 0; i < taskSize; i += 2)
		{
			//circle equation: x*x+y*y<=r*r
			x = pointsToCheck[i];
			y = pointsToCheck[i + 1];
			temp = x*x + y*y;
			if (temp <= circleEquationConstant)
			{
				myDensityResult++;
			}
		}

		MPI_Send(
			&myDensityResult, 1, MPI_INT,
			root, 0, MPI_COMM_WORLD
			);

		myDensityResult = 0;

		MPI_Recv(
			pointsToCheck, taskSize, MPI_DOUBLE,
			root, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE
			);

		//cant be in rand!
	} while (pointsToCheck[0] != finVal);
}
