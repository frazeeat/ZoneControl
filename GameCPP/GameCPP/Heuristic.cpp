#include "Heuristic.h"

double Heuristic::feature1(BreakthroughState &state, int row, int col, char cell){
	/* Current generic feature name 'feature1'
	 *   More descriptive name: ADVANCE
	 * Feature: For the given piece, add its distance from its own starting rows.
	 		Return the (home sum - away sum).
	 */
	int distance = 0;


	if (cell == state.HOMESYM) {
		distance = row;
	} else if (cell == state.AWAYSYM) {
		distance = 7 - row;
	}
	//distance *= distance;
	//printf("Distance: %d", distance);
	if (cell == state.HOMESYM){
		return distance;
	} else {
		return -1 * distance;
	}

}

double Heuristic::feature2(BreakthroughState &state, int row, int col, char cell){
	/* Current generic feature name 'feature2'
	 *  More descriptive name: SUPPORT
	 * Description: For given piece, check to see if it has a supporting piece behind it.
	 *     Pieces with an additonal allied piece behind it have been seen to be more defensively secure.
	 */

	double score;
	if (cell == state.HOMESYM && row != 0 && state.getCell(row-1, col) == cell) {
		score = 1;
	} else if (cell == state.AWAYSYM && row != 7 && state.getCell(row+1, col) == cell){
		score = 1;
	} else {
		score = 0;
	}
	//printf("Score: %f", score);
	if (cell == state.HOMESYM) {
		return score;
	} else {
		return -1 * score;
	}

}

double Heuristic::feature3(BreakthroughState &state, int row, int col, char cell) {
	/* Descriptive feature name: WALL
	 * Description: For each piece, award 1 credit for each allied piece adjacent to it horizontally.
	 * 	ex/ W.W.W -> 0 credits.  .WW. -> is worth 2 (1 for each piece...should we change that?
	 * 		.WWW. -> worth 4 credits (1 for each edge piece, 2 for the center piece)
	 * 			alternatively, make it worth 2 points, and the previous .WW. worth only 1 point.
	 */

	double score = 0;
	
	if (cell == state.HOMESYM || cell == state.AWAYSYM) {
		if (col != 0 && state.getCell(row, col-1) == cell) {
			score++;
		}
		if (col != 7 && state.getCell(row, col+1) == cell) {
			score++;
		}
	}
	//printf("H3 Score: %f\n", score);
	if (cell == state.HOMESYM) {
		return score;
	} else {
		return -1 * score;
	}

}

double Heuristic::feature4(BreakthroughState &state, int row, int col, char cell) {
	/*
	 * For given piece, assign it points, with more being given the closer to the center of the board.
	 * 	8 columns, so 4 different distances.
	 * 		........ give edges 0, 1-in .5, 1-out 1, and center 1.5
	 */

	double multiplier = 1.0;
	double score = 0;
	
	if (cell == state.HOMESYM || cell == state.AWAYSYM) {
		switch(col) {
			case 0: score = 0;
			case 1: score = .5;
			case 2: score = 1;
			case 3: score = 1.5;
			case 4: score = 1.5;
			case 5: score = 1;
			case 6: score = .5;
			case 7: score = 0;
			default: score = 0;
		}
	}	

	if (cell == state.HOMESYM) {
		return score;
	} else {
		return -1 * score;
	}

}

/*

Defensive play - if my piece is threatened by my own piece, it is "DEFENSIVE" play.


Offensive play
*/

double Heuristic::defensivePlayFeature(BreakthroughState &state, int row, int col, char cell) {
	/*
	 * Award points for pieces that threaten ally-controlled squares.
	 * 
	 */
	double score = 0;

	if (cell == state.HOMESYM && row != 7) {
		if (col != 0 && cell == state.getCell(row+1, col-1)) {
			score++;
		}
		if (col != 7 && cell == state.getCell(row+1, col+1)) {
			score++;
		}
	} else if (cell == state.AWAYSYM && row != 0) {
		if (col != 0 && cell == state.getCell(row-1, col-1)) {
			score++;
		}
		if (col != 7 && cell == state.getCell(row-1, col+1)) {
			score++;
		}
	}
	
	//if (cell == 
		return score;
}



double Heuristic::evaluateState(BreakthroughState &state){
	int rows = state.ROWS;
	int cols = state.COLS;
	double score = 0;
	// Weights should ideally add up to 1.0
	double w1 = .45,
	       w2 = .25,
	       w3 = .25,
	       w4 = .05;
	/* For each feature: 
	 *	Calculate the score of it - >0 means it favors HOME, <0 favors AWAY.
	 *	Sum the results of the features, using different weights, in this way
	 *	SCORE = (W1 * F1(S)) + (W2 * F2(S)) + (W3 * F3(S))
	*/
	char cell;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) { //heh. c plus plus. heh.
			cell = state.getCell(r, c);
			if (cell == state.HOMESYM || cell == state.AWAYSYM) {
				score += w1 * feature1(state, r, c, cell);
				score += w2 * feature2(state, r, c, cell);
				score += w3 * feature3(state, r, c, cell);
				score += w4 * feature4(state, r, c, cell);
			}
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
