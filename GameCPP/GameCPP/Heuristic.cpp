#include "Heuristic.h"

double Heuristic::firstHeuristic(BreakthroughState &state,double weight){
	
	int rows = state.ROWS;
	int cols = state.COLS;
	std::vector<char> board = *state.getBoard1D();
	for (int i = 0; i < rows*cols;i++){
		std::cout << board[i] <<std::endl;
	}
	
	return 0.0;
}