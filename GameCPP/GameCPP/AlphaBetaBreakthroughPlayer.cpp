#include "AlphaBetaBreakthroughPlayer.h"
#include "BreakthroughMove.h"
#include "BreakthroughState.h"
#include "Heuristic.h"


AlphaBetaBreakthroughPlayer::AlphaBetaBreakthroughPlayer(std::string nickname)
: GamePlayer(nickname, "Breakthrough") {}
Heuristic Eval;
long BeginTurnTime;
const long MAX_TURN_TIME = 5;
GameMove* AlphaBetaBreakthroughPlayer::getMove(GameState &state,
	const std::string &lastMv) {
	
	BreakthroughState st = static_cast<BreakthroughState&>(state);

	for (int i = 0; i < DepthLimit; i++) {
		if (i % 2 == 0){
			mvStack[i] = ScoredBreakthroughMove(0, 0, 0, 0, ((st.getWho() == Who::HOME) ? -DBL_MAX : DBL_MAX));
		}
		else{
			mvStack[i] = ScoredBreakthroughMove(0, 0, 0, 0, ((st.getWho() == Who::AWAY) ? -DBL_MAX : DBL_MAX));
		}
	}
	/*std::vector<BreakthroughMove> mvArray;
	/for (int r = 0; r < st.ROWS; r++) {
		for (int c = 0; c < st.COLS; c++) {
			int rowDelta = state.getWho() == Who::HOME ? +1 : -1;
			for (int dc = -1; dc <= +1; dc++) {
				BreakthroughMove mv(r, c, r + rowDelta, c + dc);
				if (state.moveOK(mv)) {
					mvArray.push_back(BreakthroughMove(mv));
				}
			}
		}
	}*/
	alphaBeta(st, 0, -DBL_MAX, DBL_MAX);
	printf("Final Score: %f", mvStack[0].score);
	return mvStack[0].Move;
}
void AlphaBetaBreakthroughPlayer::alphaBeta(BreakthroughState brd, int currDepth,
	double alpha, double beta){
	boolean isMaximize = (brd.getWho() == Who::HOME);
	boolean isMinimize = !isMaximize;
	boolean isTerminal = terminalValue(brd, &mvStack[currDepth]);
	if (isTerminal) {
		
	}
	else if (currDepth == DepthLimit-1) {
		mvStack[currDepth].setScore(Eval.evaluateState(brd));// evalBoard(brd));
		//printf("Score: %d", mvStack[currDepth].score);
	}
	else {

		std::vector<BreakthroughMove> mvArray;
		for (int r = 0; r < brd.ROWS; r++) {
			for (int c = 0; c < brd.COLS; c++) {
				int rowDelta = brd.getWho() == Who::HOME ? +1 : -1;
				for (int dc = -1; dc <= +1; dc++) {
					BreakthroughMove mv(r, c, r + rowDelta, c + dc);
					if (brd.moveOK(mv)) {
						mvArray.push_back(BreakthroughMove(mv));
					}
				}
			}
		}
		std::random_shuffle(mvArray.begin(), mvArray.end());
		double bestScore = (isMaximize ?
		-DBL_MAX : DBL_MAX);
		ScoredBreakthroughMove* bestMove = &mvStack[currDepth];
		ScoredBreakthroughMove* nextMove = &mvStack[currDepth + 1];
		bestMove->set(mvArray[0].row1(), mvArray[0].col1(), mvArray[0].row2(), mvArray[0].col2(), bestScore);
		for (int i = 0; i < mvArray.size();i++){

			ScoredBreakthroughMove tempMv = ScoredBreakthroughMove(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), 0);
			BreakthroughState tempBrd = brd;
			brd.makeMove(*tempMv.Move);
			alphaBeta(brd, currDepth + 1, alpha, beta);  // Check out move
			brd = tempBrd;
			//bestMove.setScore(mvStack[currDepth].score);
			//nextMove.setScore(mvStack[currDepth + 1].score);
			//bestMove.set(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), mvStack[currDepth].score);
			//bestMove = mvStack[currDepth];
			//nextMove = mvStack[currDepth + 1];
			// Check out the results, relative to what we've seen before
			if (isMaximize && (nextMove->score > bestMove->score)) {
				bestMove->set(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), nextMove->score);
				//mvStack[currDepth].set(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), nextMove.score);
				//printf("Current Depth: %d Maximum Score: %f\n",currDepth, nextMove->score);
			}
			else if (!isMaximize && (nextMove->score < bestMove->score)) {
				bestMove->set(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), nextMove->score);
				//mvStack[currDepth].set(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), nextMove.score);
				//printf("Current Depth: %d Minimal Score: %f\n",currDepth, nextMove->score);
			}

			// Update alpha and beta. Perform pruning, if possible.
			//printf("Test");
			if (isMinimize) {
				beta = min(bestMove->score, beta);
				if (beta <= alpha || beta == -DBL_MAX) {//bestMove.score <= alpha || bestMove.score == -DBL_MAX) {
					return;
				}
			}
			else {
				alpha = max(bestMove->score, alpha);
				if (alpha >= beta || alpha == DBL_MAX) {
					return;
				}
			}
		}
	}
}

boolean AlphaBetaBreakthroughPlayer::terminalValue(GameState &brd, ScoredBreakthroughMove *mv) {
	Status status = brd.getStatus();
	boolean isTerminal = true;

	if (status == Status::HOME_WIN) {
		mv->setScore(DBL_MAX);
	}
	else if (status == Status::AWAY_WIN) {
		mv->setScore(-DBL_MAX);
	}
	else if (status == Status::DRAW) {
		mv->setScore(0);
	}
	else {
		isTerminal = false;
	}
	return isTerminal;
}