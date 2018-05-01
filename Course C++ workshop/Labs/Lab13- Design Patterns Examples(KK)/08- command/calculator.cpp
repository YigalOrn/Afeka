#pragma warning (disable : 4786)

#include "calculator.h"

#include <iostream>
using namespace std;

Calculator::Calculator()
{
	numOfSteps=0;
}

void Calculator::compute(char operand , float number)
{
	pool.push_back(oper.operate(operand , number , true));
	numOfSteps++;
}

void Calculator::undo(int levelsToUndo)
{
	cout << "****** undo (" << levelsToUndo << ") ******" << endl;

	for (int i=0 ; i < levelsToUndo ; i++)
	{
		if( numOfSteps > 0 )
		{
			pool[--numOfSteps]->unExecute();
		}
	}
}

void Calculator::redo(int levelsToRedo)
{		
	cout << "****** redo (" << levelsToRedo << ") ******" << endl;

	for (int i=0 ; i < levelsToRedo ; i++)
	{			
		if( numOfSteps < (int)pool.size() )
		{
			pool[numOfSteps++]->execute();
		}
	}
}


