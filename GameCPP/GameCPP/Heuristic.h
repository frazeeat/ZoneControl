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


	double feature1(BreakthroughState &state, int row, int col, char cell);

	double feature2(BreakthroughState &state, int row, int col, char cell);

	double feature3(BreakthroughState &state, int row, int col, char cell);

	double feature4(BreakthroughState &state, int row, int col, char cell);
	
	double defensivePlayFeature(BreakthroughState &state, int row, int col, char cell);

	double evaluateState(BreakthroughState &state);
	
	double firstHeuristic(BreakthroughState &state, double weight);
};
#endif
