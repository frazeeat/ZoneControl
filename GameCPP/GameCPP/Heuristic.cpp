#include "Heuristic.h"

double Heuristic::feature1(BreakThroughState &state){
	/* Current generic feature name 'feature1'
	 * Feature: For each piece, add its distance from its own starting rows.
	 		Return the (home sum - away sum).
	 */

	double HomeSum = 0;
	double AwaySum = 0;
	std::vector<char> board = *state.getBoard1D();

	char currentPlayerSymbol = state.getCurPlayerSymbol();

	for (int i = 0; i < state.ROWS; i++) {
		for (int j = 0; j < state.COLS; j++) {

			char cell = state.getCell(i, j);

			if ( cell == state.getCurPlayerSymbol()) {
				HomeSum += 7 - i;
			} else if (cell == state.getCurOpponentSymbol()) {
				AwaySum += i;
			} else
				continue;
		}
	}

	if (state.getCurPlayerCymbol() == state.HOMESYM)
		return HomeSum - AwaySum;
	else
		return AwaySum - HomeSum;
}

double Heuristic::feature2(BreakThroughState &state){
	/* Current generic feature name 'feautre2'
	 *
	 */
	
	return 0.0;
}

double Heuristic::evaluateState(BreakthroughState &state){
	int rows = state.ROWS;
	int cols = state.COLS;
	double score = 0;

	/* For each feature: 
	 *	Calculate the score of it - >0 means it favors HOME, <0 favors AWAY.
	 *	Sum the results of the features, using different weights, in this way
	 *	SCORE = (W1 * F1(S)) + (W2 * F2(S)) + (W3 * F3(S))
	*/

	score += feature1(state);
	score += feature2(state);

	return score;

}

double Heuristic::firstHeuristic(BreakthroughState &state,double weight){
	
	int rows = state.ROWS;
	int cols = state.COLS;
	std::vector<char> board = *state.getBoard1D();
	for (int i = 0; i < rows*cols;i++){
		std::cout << board[i] <<std::endl;
	}
	
	return 0.0;
}
