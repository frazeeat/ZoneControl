#include "AlphaBetaBreakthroughPlayer.h"
#include "BreakthroughMove.h"
#include "BreakthroughState.h"


AlphaBetaBreakthroughPlayer::AlphaBetaBreakthroughPlayer(std::string nickname)
: GamePlayer(nickname, "Breakthrough") {}
const double MAX_SCORE = 100;
const int DEPTH_LIMIT = 3;
GameMove* AlphaBetaBreakthroughPlayer::getMove(GameState &state,
	const std::string &lastMv) {
	BreakthroughState st = static_cast<BreakthroughState&>(state);
	std::vector<BreakthroughMove> mvArray;
	for (int r = 0; r < st.ROWS; r++) {
		for (int c = 0; c < st.COLS; c++) {
			int rowDelta = state.getWho() == Who::HOME ? +1 : -1;
			for (int dc = -1; dc <= +1; dc++) {
				BreakthroughMove mv(r, c, r + rowDelta, c + dc);
				if (state.moveOK(mv)) {
					mvArray.push_back(BreakthroughMove(mv));
				}
			}
		}
	}

	return new BreakthroughMove(mvArray[rand() % mvArray.size()]);
}
void AlphaBetaBreakthroughPlayer::alphaBeta(BreakthroughState brd, int currDepth,
	double alpha, double beta){
	boolean isMaximize = (brd.getWho() == Who::HOME);
	boolean isMinimize = !isMaximize;
	boolean isTerminal = terminalValue(brd, mvStack[currDepth]);
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
	if (isTerminal) {

	}
	else if (currDepth == DEPTH_LIMIT) {
		mvStack[currDepth].setScore(0);// evalBoard(brd));
	}
	else {
		double bestScore = (isMaximize ?
		DBL_MIN : DBL_MAX);
		ScoredBreakthroughMove bestMove;
		ScoredBreakthroughMove nextMove;
		
		for (int i = 0; i < mvArray.size();i++){
			bestMove.set(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), bestScore);
			ScoredBreakthroughMove tempMv = ScoredBreakthroughMove(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), 0);
			BreakthroughState tempBrd = brd;
			brd.makeMove(tempMv);
			alphaBeta(brd, currDepth + 1, alpha, beta);  // Check out move
			brd = tempBrd;

			// Check out the results, relative to what we've seen before
			if (isMaximize && nextMove.score > bestMove.score) {
				bestMove.set(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), nextMove.score);
			}
			else if (!isMaximize && nextMove.score < bestMove.score) {
				bestMove.set(mvArray[i].row1(), mvArray[i].col2(), mvArray[i].row2(), mvArray[i].col2(), nextMove.score);
			}

			// Update alpha and beta. Perform pruning, if possible.
			if (isMinimize) {
				beta = min(bestMove.score, beta);
				if (bestMove.score <= alpha || bestMove.score == -MAX_SCORE) {
					return;
				}
			}
			else {
				alpha = max(bestMove.score, alpha);
				if (bestMove.score >= beta || bestMove.score == MAX_SCORE) {
					return;
				}
			}
		}
	}
}

boolean AlphaBetaBreakthroughPlayer::terminalValue(GameState &brd, ScoredBreakthroughMove mv) {
	Status status = brd.getStatus();
	boolean isTerminal = true;

	if (status == Status::HOME_WIN) {
		mv.setScore(MAX_SCORE);
	}
	else if (status == Status::AWAY_WIN) {
		mv.setScore(-MAX_SCORE);
	}
	else if (status == Status::DRAW) {
		mv.setScore(0);
	}
	else {
		isTerminal = false;
	}
	return isTerminal;
}