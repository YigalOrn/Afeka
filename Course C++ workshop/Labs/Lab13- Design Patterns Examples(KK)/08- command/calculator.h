#ifndef __CALCULATOR_H

#include <vector>
using namespace std;

#include "Operations.h"

class Calculator
{
	vector<Operator*> pool;
	Operations oper;
	int numOfSteps;

public:
	Calculator();

	void compute(char operand , float number);
	void undo(int levelsToUndo);
	void redo(int levelsToRedo);
};

#endif // __CALCULATOR_H