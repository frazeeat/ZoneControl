#include "AlphaBetaBreakthroughPlayer.h"
#include "BreakthroughMove.h"
#include "BreakthroughState.h"
#include "Heuristic.h"


AlphaBetaBreakthroughPlayer::AlphaBetaBreakthroughPlayer(std::string nickname)
	: GamePlayer(nickname, "Breakthrough") {

}
Heuristic Eval;
time_t BeginTurnTime;

long MAX_TURN_TIME = 2;
int movesMade = 0;
bool first = true;
//int timeSpent = 0;
GameMove* AlphaBetaBreakthroughPlayer::getMove(GameState &state,
	const std::string &lastMv) {
	BreakthroughState st = static_cast<BreakthroughState&>(state);
	if (lastMv.size() == 2 || stoi(lastMv.substr(4, 1)) == 0 || stoi(lastMv.substr(4, 1)) == 7) {
		MAX_TURN_TIME = 2;
		movesMade = 0;
	}
	if (first) {
		for (int j = 0; j < MAX_DEPTH_LIMIT; j++) {
			if (j % 2 == 0) {
				mvStack[j] = ScoredBreakthroughMove(0, 0, 0, 0, ((st.getWho() == Who::HOME) ? -DBL_MAX : DBL_MAX));
			}
			else {
				mvStack[j] = ScoredBreakthroughMove(0, 0, 0, 0, ((st.getWho() == Who::AWAY) ? -DBL_MAX : DBL_MAX));
			}
		}
		first = false;
	}
	else {
		for (int j = 0; j < MAX_DEPTH_LIMIT; j++) {
			if (j == 0) {
				mvStack[j] = ScoredBreakthroughMove(0, 0, 0, 0, ((st.getWho() == Who::HOME) ? -DBL_MAX : DBL_MAX));
			}
			else if (j % 2 == 0) {
				mvStack[j].set(0, 0, 0, 0, ((st.getWho() == Who::HOME) ? -DBL_MAX : DBL_MAX));
			}
			else {
				mvStack[j].set(0, 0, 0, 0, ((st.getWho() == Who::AWAY) ? -DBL_MAX : DBL_MAX));
			}
		}
	}
	BeginTurnTime = time(nullptr);
	int i = 3;
	BreakthroughMove mv = BreakthroughMove();
	int curtime = time(nullptr) - BeginTurnTime;
	//if ((240 - timeSpent) > 20) {
	while (i < MAX_DEPTH_LIMIT && curtime < MAX_TURN_TIME) {
		DepthLimit = i;
		alphaBeta(st, 0, -DBL_MAX, DBL_MAX);
		curtime = time(nullptr) - BeginTurnTime;
		if (curtime < MAX_TURN_TIME) {
			mv = *mvStack[0].Move;
			if (mvStack[0].score == DBL_MAX || mvStack[0].score == -DBL_MAX) {
				break;
			}
			i++;
		}
	}
	//}
	//timeSpent += curtime;
	//printf("Time: %d\n", timeSpent);
	mvStack[0].set(mv.row1(), mv.col1(), mv.row2(), mv.col2(), 0);
	movesMade++;
	if (movesMade == 4) {
		MAX_TURN_TIME = 5;
	}
	if (mvStack[0].Move->col1() == 0 && mvStack[0].Move->col2() == 0 && mvStack[0].Move->row1() == 0 && mvStack[0].Move->row2() == 0) {
		DepthLimit = 3;
		alphaBeta(st, 0, -DBL_MAX, DBL_MAX);
	}
	return mvStack[0].Move;
}
void AlphaBetaBreakthroughPlayer::alphaBeta(BreakthroughState brd, int currDepth,
	double alpha, double beta) {
	std::vector<BreakthroughMove> mvArray;
	bool isMaximize = (brd.getWho() == Who::HOME);
	bool isMinimize = !isMaximize;
	bool isTerminal = terminalValue(brd, &mvStack[currDepth]);
	bool iWin = false;

	if (isTerminal) {

	}
	else if (currDepth == DepthLimit) {
		mvStack[currDepth].setScore(Eval.evaluateState(brd));
	}
	else {
		int row = 7, init = 0, rowDelta = isMaximize ? +1 : -1;
		for (int r = 0; r < brd.ROWS; r++) {
			for (int c = 0; c < brd.COLS; c++) {
				for (int dc = -1; dc <= +1; dc++) {
					BreakthroughMove mv(r, c, r + rowDelta, c + dc);
					if (brd.moveOK(mv)) {
						mvArray.push_back(BreakthroughMove(mv));
						if (currDepth == 0) {
							if (doesThisWin(mv, brd)) {
								mvArray.clear();
								mvArray.push_back(BreakthroughMove(mv));
								iWin = true;
							}
						}
					}
				}
			}
		}
		if (!iWin) {
			std::random_shuffle(mvArray.begin(), mvArray.end());
		}
		double bestScore = (isMaximize ?
			-DBL_MAX : DBL_MAX);
		ScoredBreakthroughMove* bestMove = &mvStack[currDepth];
		ScoredBreakthroughMove* nextMove = &mvStack[currDepth + 1];
		bestMove->set(mvArray[0].row1(), mvArray[0].col1(), mvArray[0].row2(), mvArray[0].col2(), bestScore);
		for (int i = 0; i < mvArray.size();i++) {

			ScoredBreakthroughMove tempMv = ScoredBreakthroughMove(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), 0);
			BreakthroughState tempBrd = brd;
			brd.makeMove(*tempMv.Move);
			alphaBeta(brd, currDepth + 1, alpha, beta);  // Check out move
			brd = tempBrd;
			if ((time(nullptr) - BeginTurnTime) > MAX_TURN_TIME) {
				return;
			}
			// Check out the results, relative to what we've seen before
			if (isMaximize && (nextMove->score > bestMove->score)) {
				bestMove->set(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), nextMove->score);
			}
			else if (!isMaximize && (nextMove->score < bestMove->score)) {
				bestMove->set(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), nextMove->score);
			}

			// Update alpha and beta. Perform pruning, if possible.
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

bool AlphaBetaBreakthroughPlayer::doesThisWin(BreakthroughMove mv, BreakthroughState brd) {
	if (brd.getWho() == Who::HOME) {
		if (mv.row2() == brd.ROWS - 1) {
			return true;
		}
	}
	else {
		if (mv.row2() == 0) {
			return true;
		}
	}
	return false;
}

bool AlphaBetaBreakthroughPlayer::terminalValue(GameState &brd, ScoredBreakthroughMove *mv) {
	Status status = brd.getStatus();
	bool isTerminal = true;

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