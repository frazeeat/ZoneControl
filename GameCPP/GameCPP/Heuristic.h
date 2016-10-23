#ifndef __CSE486AIProject__Heuristic__
#define __CSE486AIProject__Heuristic__
#include "BreakthroughState.h"
#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>

class Heuristic{
public:
	double alpha;
	double beta;

	double firstHeuristic(BreakthroughState &state, double weight);
};
#endif