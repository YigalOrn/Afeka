#include <mpi.h>

#include <iostream>
#include<iomanip>
#include <time.h>
//#include <cmath>
using namespace std;


#include "StaticPrototypes.h"


int main(int argc, char *argv[])
{
	int numprocs;
	int myRank;
	

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	

	if (argc != 3)
	{
		cout << "# command line paramaters count error : argc!=3 #" << endl;
		cout << "# additional command line paramaters are: radius, accuracy #" << endl;
		cout.flush();
		MPI_Abort(MPI_COMM_WORLD, 1);
	}


	int root = 0;

	//we see why we dont actually need radius, we just wanted to show good flexibility :)
	double radius;
	//number of rectangles when thinking of the graph
	int accuracy;
	
	//the step that should be done, from accuracy we set the rectangular len on x axis
	double dx;
	//for root to accumulate all local results send to him
	double sum = 0;
	//for slave to put local result
	double localSum = 0;
	//defines from where to where should each slave check in jumps of dx
	double segment[2];
	//a buffer for bcast to send initial data to all slaves(root is not interesting)
	double initParams[2];

	if (myRank == root)
	{
		radius = atof(argv[1]);
		accuracy = atoi(argv[2]);
		
		//pls notice i leave one process for master, so the others should be divisor of accuracy
		if (accuracy % (numprocs - 1) != 0)
		{
			cout << "# accuracy % (numprocs - 1) != 0 #" << endl;
			MPI_Abort(MPI_COMM_WORLD, 1);
		}

		/*
		we have accuracy(number) rectangles. 
		each slave gets his portion of rectangles to check,
		the number of rectangles that each slave has is bound by the segment[] data,
		it holds the lower and upper bound and each slave steps dx each calculation
		until he gets to the upper bound given in segment, for each calculation he 
		accumulates some partial sum of the numeric integral, 
		this result is sent to the master fro farther accumulation.
		*/
		dx = (radius*1.0) / accuracy;

		initParams[0] = radius;
		initParams[1] = dx;
	}
	

	MPI_Bcast(initParams, 2, MPI_DOUBLE, root, MPI_COMM_WORLD);
	

	if (myRank == root)
	{
		//we divide the rectangles among the slaves, should be divisible!
		int numOfRectanglesPerSlave = accuracy / (numprocs - 1);
		
		//first initialization
		segment[0] = 0;//left bound
		segment[1] = numOfRectanglesPerSlave*dx;//right bound

		for (int i = 1; i < numprocs; i++)
		{
			MPI_Send(segment, 2, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
			//left bound <-- right bound
			segment[0] = segment[1];
			//right bound <-- left bound + rectangle sequence
			segment[1] = segment[0] + numOfRectanglesPerSlave*dx;
		}
	}
	else
	{
		//init from bcast
		radius = initParams[0];
		dx = initParams[1];

		MPI_Recv(segment, 2, MPI_DOUBLE, root, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		slaveDoPartialIntegration(radius, segment, dx, localSum);
	}


	//slaves individual localSum are summed into root sum
	MPI_Reduce(
		&localSum, &sum, 1, MPI_DOUBLE,
		MPI_SUM,
		root, MPI_COMM_WORLD
		);


	if (myRank == root)
	{
		masterPrintRes(sum, radius);
	}


	MPI_Finalize();
	return 0;

}//main

void masterPrintRes(const double& sum, const double& radius)
{
	cout << "weak numerical integration result is -\t" << sum << endl;
	cout << "PI by calculator is -\t3.141592654" << endl;
	cout << "derived PI value is -\t" << setprecision(10) << (sum * 4 / (radius*radius)) << endl;
}

void slaveDoPartialIntegration(const double& radius, const double* segment, const double& dx,
	double& localSum)
{
	/*
	slave gets his "domain" and he knows dx
	(all this params are carefully calculated by the master so there are no
	duplicates or overlapping nor overflowing)

	then each slaves calculates one rectangle at a time,stepping dx from one rect to another until the right "domain" bound is reached, each step is accumulated using the loaclSum 

	because of the static nature of work each slaves performs calculation once
	those calcs are then reduced to the master for output.
	*/

	double leftBound = segment[0], rightBound = leftBound + dx;
	double x;

	while (rightBound < segment[1])
	{
		x = ((rightBound - leftBound) / 2.0) + leftBound;

		//the integral to calc is the possitve circle equation: y=+root(R^2-x^2) 
		localSum += sqrt(radius*radius - x*x)*dx;

		leftBound = rightBound;
		rightBound = leftBound + dx;
	}
}

