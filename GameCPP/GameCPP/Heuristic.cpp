#include "Heuristic.h"

double Heuristic::feature1(BreakthroughState &state, int row, int col){
	/* Current generic feature name 'feature1'
	 *   More descriptive name: ADVANCE
	 * Feature: For the given piece, add its distance from its own starting rows.
	 		Return the (home sum - away sum).
	 */
	int distance = 0;
	char cell = state.getCell(row, col);
	if (cell == state.HOMESYM) {
		distance = row;
	} else if (cell == state.AWAYSYM) {
		distance = 7 - row;
	}
	//printf("Distance: %d", distance);
	if (state.getCurPlayerSym() == state.HOMESYM){
		return distance;
	} else {
		return -1 * distance;
	}

/*
	double HomeSum = 0;
	double AwaySum = 0;
	std::vector<char> board = *state.getBoard1D();

	char currentPlayerSymbol = state.getCurPlayerSym();

	for (int i = 0; i < state.ROWS; i++) {
		for (int j = 0; j < state.COLS; j++) {

			char cell = state.getCell(i, j);

			if (cell == state.getCurPlayerSym()) {
				HomeSum += 7 - i;
			} else if (cell == state.getCurOpponentSym()) {
				AwaySum += i;
			} else
				continue;
		}
	}
	printf("Home: %d Away: %d", HomeSum, AwaySum);
	if (state.getCurPlayerSym() == state.HOMESYM)
		return HomeSum - AwaySum;
	else
		return AwaySum - HomeSum;
*/
}

double Heuristic::feature2(BreakthroughState &state, int row, int col){
	/* Current generic feature name 'feature2'
	 *  More descriptive name: SUPPORT
	 * Description: For given piece, check to see if it has a supporting piece behind it.
	 *     Pieces with an additonal allied piece behind it have been seen to be more defensively secure.
	 */

	char cell = state.getCell(row, col);
	double score;
	if (cell == state.HOMESYM && row != 0 && state.getCell(row-1, col) == cell) {
		score = 1;
	} else if (cell == state.AWAYSYM && row != 7 && state.getCell(row+1, col) == cell){
		score = 1;
	} else {
		score = 0;
	}
	//printf("Score: %f", score);
	if (state.getCurPlayerSym() == state.HOMESYM) {
		return score;
	} else {
		return -1 * score;
	}

/*
	double score = 0;
	/
	   For each location, check if it belongs to current player. If so, check if there is another allied piece behind it.
	   	Award 1 credit for each support piece. ex/ 3 contiguous pieces in a column is worth 2 points.

	/

	for (int i = 0; i < state.ROWS; i++) {
		for (int j = 0; j < state.COLS; j++) {
			char cell = state.getCell(i, j);

			if (cell == state.HOMESYM){ // If home piece, add supports to score
				if (i != 7 && (state.getCell(i+1, j) == state.HOMESYM)) { // If not last in column.
					score++; // Grant one point for the supported piece.
				}
			} else if (cell == state.AWAYSYM) { //If away piece, subtract supports from score.
				if (i != 0 && (state.getCell(i-1, j) == state.AWAYSYM)) { // If not last in column.
					score--;
				}
			}
		}
	}
	printf("H2: Score %d", score);
	if (state.getCurPlayerSym() == state.HOMESYM) {
		return score;
	} else {
		return score * -1;
	}
	*/
}

double Heuristic::feature3(BreakthroughState &state, int row, int col) {
	/* Descriptive feature name: WALL
	 * Description: For each piece, award 1 credit for each allied piece adjacent to it horizontally.
	 * 	ex/ W.W.W -> 0 credits.  .WW. -> is worth 2 (1 for each piece...should we change that?
	 * 		.WWW. -> worth 4 credits (1 for each edge piece, 2 for the center piece)
	 * 			alternatively, make it worth 2 points, and the previous .WW. worth only 1 point.
	 */

	char cell = state.getCell(row, col);
	double score = 0;

	if (col != 0 && state.getCell(row, col-1) == cell) {
		score++;
	}
	if (col != 7 && state.getCell(row, col+1) == cell) {
		score++;
	}
	//printf("H3 Score: %f\n", score);
	if (state.getCurPlayerSym() == state.HOMESYM) {
		return score;
	} else {
		return -1 * score;
	}

/*

	double score = 0;

	for (int i = 0; i < state.ROWS; i++) {
		for (int j = 0; j < state.COLS; j++) {
			char cell = state.getCell(i, j);

			if (cell == state.HOMESYM) { // If home piece, add to score.
				if (j != 0 && (state.getCell(i, j-1) == state.HOMESYM)) {
					score++;
				}
				if (j != 7 && (state.getCell(i, j+1) == state.HOMESYM)) {
					score++;
				}
			} else if (cell == state.AWAYSYM) { // If away piece, subtract from score.
				if (j != 0 && (state.getCell(i, j-1) == state.AWAYSYM)) {
					score--;
				}
				if (j != 7 && (state.getCell(i, j+1) == state.AWAYSYM)) {
					score--;
				}
			}
		}
	}
	printf(" H3: Score %d\n", score);
	if (state.getCurPlayerSym() == state.HOMESYM) {
		return score;
	} else {
		return -1 * score;
	}
*/
}

double Heuristic::evaluateState(BreakthroughState &state){
	int rows = state.ROWS;
	int cols = state.COLS;
	double score = 0;
	double w1 = .6,
	       w2 = .2,
	       w3 = .2;
	/* For each feature: 
	 *	Calculate the score of it - >0 means it favors HOME, <0 favors AWAY.
	 *	Sum the results of the features, using different weights, in this way
	 *	SCORE = (W1 * F1(S)) + (W2 * F2(S)) + (W3 * F3(S))
	*/
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) { //heh. c plus plus. heh.
			score += w1 * feature1(state, r, c);
			score += w2 * feature2(state, r, c);
			score += w3 * feature3(state, r, c);
		}
	}


	//printf("Score: %f\n", score);
	//score += w1 * feature1(state);
	//score += w2 * feature2(state);
	//score += w3 * feature3(state);
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
