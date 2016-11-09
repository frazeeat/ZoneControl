#include "AlphaBetaBreakthroughPlayer.h"
#include "BreakthroughMove.h"
#include "BreakthroughState.h"
#include "Heuristic.h"
#include <random>



AlphaBetaBreakthroughPlayer::AlphaBetaBreakthroughPlayer(std::string nickname)
: GamePlayer(nickname, "Breakthrough") {
	// In constructor, create the initial Zobrist hash of the board,
	//      and populate the array of piece/locations.
	Zobrist_hash_board = 0;
	int white = 0,
		black = 1;
	std::random_device rnd;
	std::mt19937_64 rng(rnd());
	std::uniform_int_distribution<long long int> dist(std::llround(0), std::llround(std::pow(2, 64)));

	// For each piece/location pair, generate a random 64 bit number to represent it.
	for (int i = 0; i < 128; i++) {
		board_pieces_hash[i] = dist(rng);
	}

	// Hash the initial board state:
	/*
	* WWWWWWWW 0
	* WWWWWWWW 1
	*   ...
	*   ...
	* BBBBBBBB 6
	* BBBBBBBB 7
	*/
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i < 2) { // White pieces
				Zobrist_hash_board = Zobrist_hash_board ^ board_pieces_hash[white * 64 + i * 8 + j];
			}
			else if (i >= 6) { // Black pieces
				Zobrist_hash_board = Zobrist_hash_board ^ board_pieces_hash[black * 64 + i * 8 + j];
			}
			// else empty, don't hash anything.
		}
	}

	// Now Zobrist_hash_board contains the hashed state of the board.
}

long long AlphaBetaBreakthroughPlayer::hash_piece(int row, int col, Who color) {
	int mod = 0;
	if (color == Who::HOME) {
		mod = 0;
	}
	else if (color == Who::AWAY) {
		mod = 1;
	}

	return board_pieces_hash[mod * 64 + row * 8 + col];
}

Heuristic Eval;
time_t BeginTurnTime;
long MAX_TURN_TIME = 2;
int movesMade = 0;
bool first = true;
//int furthestRowHome=1;
//int furthestRowAway=6;
GameMove* AlphaBetaBreakthroughPlayer::getMove(GameState &state,
	const std::string &lastMv) {
	BreakthroughState st = static_cast<BreakthroughState&>(state);
	if (lastMv.length() < 4) {
		MAX_TURN_TIME = 2;
		movesMade = 0;
	}
	/*if (lastMv.length() > 4){
		if (state.getWho() == Who::HOME){
			if (furthestRowAway > stoi(lastMv.substr(4, 1))){
				furthestRowAway--;
			}
		}
		else{
			if (furthestRowHome < stoi(lastMv.substr(4, 1))){
				furthestRowHome++;
			}
		}
	}*/
	/*
	if (furthestRowAway<3 || furthestRowHome>4){
		//MAX_TURN_TIME = 7;
		DepthLimit = 5;
	}
	else{
		DepthLimit = 3;
	}
	*/
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
	if (curtime < 0) {
		printf("This is what broke");
	}
	while (i < MAX_DEPTH_LIMIT && curtime<MAX_TURN_TIME){
		DepthLimit = i;
		alphaBeta(st, 0, -DBL_MAX, DBL_MAX);
		curtime = time(nullptr) - BeginTurnTime;
		if (curtime < MAX_TURN_TIME){
			mv = *mvStack[0].Move;
			if (mvStack[0].score == DBL_MAX||mvStack[0].score == -DBL_MAX) {
				break;
			}
			i++;
		}
	}
	mvStack[0].set(mv.row1(),mv.col1(),mv.row2(),mv.col2(),0);
	movesMade++;
	if (movesMade == 4){
		MAX_TURN_TIME = 5;
	//	DepthLimit = 5;
	}
	//printf("Score: %f", mvStack[0].score);
	/*
	if (state.getWho() == Who::HOME){
		if (furthestRowHome < mv->row2()){
			furthestRowHome++;
		}
	}
	else{
		if (furthestRowAway > mv->row2()){
			furthestRowAway--;
		}
	}
	*/
	return mvStack[0].Move;
}
void AlphaBetaBreakthroughPlayer::alphaBeta(BreakthroughState brd, int currDepth,
	double alpha, double beta){
	std::vector<BreakthroughMove> mvArray;
	bool isMaximize = (brd.getWho() == Who::HOME);
	bool isMinimize = !isMaximize;
	bool isTerminal = terminalValue(brd, &mvStack[currDepth]);
	bool iWin = false;
	
	if (isTerminal) {
		
	}
	else if (currDepth == DepthLimit) {
		mvStack[currDepth].setScore(Eval.evaluateState(brd));// evalBoard(brd));
		//printf("Score: %f\n", mvStack[currDepth].score);
	}
	else {
		int row = 7, init = 0, rowDelta = isMaximize? +1:-1;
		//if (isMaximize){
		//	rowDelta = 1;
			//init = 0;
			//row = furthestRowHome+1;
		//}
		//else{
		//	rowDelta = -1;
			//init = furthestRowAway-1;
			//furthestRowAway = 7;
			//row = brd.ROWS;
		//}
		for (int r = 0; r < brd.ROWS; r++) {
			for (int c = 0; c < brd.COLS; c++) {
				for (int dc = -1; dc <= +1; dc++) {
					BreakthroughMove mv(r, c, r + rowDelta, c + dc);
					if (brd.moveOK(mv)) {
						mvArray.push_back(BreakthroughMove(mv));
						/*if (isMaximize){
							furthestRowHome = r;
						}
						else{
							if (r < furthestRowAway){
								furthestRowAway = r;
							}
						}*/
						if (currDepth == 0){
							if (doesThisWin(mv, brd)){
								mvArray.clear();
								mvArray.push_back(BreakthroughMove(mv));
								iWin = true;
							}
						}
					}
				}
			}
		}
		if (!iWin){
			std::random_shuffle(mvArray.begin(), mvArray.end());
		}
		double bestScore = (isMaximize ?
		-DBL_MAX : DBL_MAX);
		ScoredBreakthroughMove* bestMove = &mvStack[currDepth];
		ScoredBreakthroughMove* nextMove = &mvStack[currDepth + 1];
		bestMove->set(mvArray[0].row1(), mvArray[0].col1(), mvArray[0].row2(), mvArray[0].col2(), bestScore);
		for (int i = 0; i < mvArray.size();i++){

			ScoredBreakthroughMove tempMv = ScoredBreakthroughMove(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), 0);
			BreakthroughState tempBrd = brd;
			//bool change = false;
			/*if (isMaximize){
				if (furthestRowHome < mvArray[i].row2()){
					furthestRowHome++;
					change = true;
				}
			}
			else{
				if (furthestRowAway > mvArray[i].row2()){
					furthestRowAway--;
					change = true;
				}
			}*/
			brd.makeMove(*tempMv.Move);
			alphaBeta(brd, currDepth + 1, alpha, beta);  // Check out move
			brd = tempBrd;
			/*if (change){
				if (isMaximize){
					furthestRowHome--;
				}
				else{
					furthestRowAway++;
				}
			}*/
			if ((time(nullptr)-BeginTurnTime)>MAX_TURN_TIME){
				return;
			}
			// Check out the results, relative to what we've seen before
			if (isMaximize && (nextMove->score > bestMove->score)) {
				bestMove->set(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), nextMove->score);
				//printf("Current Depth: %d Maximum Score: %f\n",currDepth, nextMove->score);
			}
			else if (!isMaximize && (nextMove->score < bestMove->score)) {
				bestMove->set(mvArray[i].row1(), mvArray[i].col1(), mvArray[i].row2(), mvArray[i].col2(), nextMove->score);
				//printf("Current Depth: %d Minimal Score: %f\n",currDepth, nextMove->score);
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

bool AlphaBetaBreakthroughPlayer::doesThisWin(BreakthroughMove mv, BreakthroughState brd){
	if (brd.getWho() == Who::HOME){
		if (mv.row2() == brd.ROWS-1){
			return true;
		}
	}
	else{
		if(mv.row2() == 0){
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