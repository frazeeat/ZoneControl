#ifndef __CSE486AIProject__AlphaBetaBreakthroughPlayer__
#define __CSE486AIProject__AlphaBetaBreakthroughPlayer__

#include "GamePlayer.h"
#include "GameMove.h"
#include "BreakthroughState.h"
#include "BreakthroughMove.h"
#include <stdio.h>
#include "ScoredBreakthroughMove.h"
#include <algorithm>
#include <stdlib.h>
#include <ctime>
#include <string>
#include "HashValue.cpp"
#include <unordered_map>

class AlphaBetaBreakthroughPlayer : public GamePlayer {
public:
	AlphaBetaBreakthroughPlayer(std::string nickname);
	bool AlphaBetaBreakthroughPlayer::doesThisWin(BreakthroughMove mv, BreakthroughState brd);
	GameMove *getMove(GameState &state,
		const std::string &lastMv) override;
private:
	void alphaBeta(BreakthroughState brd, int currDepth,
		double alpha, double beta);
	bool terminalValue(GameState &brd, ScoredBreakthroughMove *mv);
	long long hash_piece(int row, int col, Who color);
	int DepthLimit = 3;
#define MAX_DEPTH_LIMIT 8
	ScoredBreakthroughMove mvStack[MAX_DEPTH_LIMIT];
	long long Zobrist_hash_board;
	long long board_pieces_hash[128];
	std::unordered_map<long long, HashValue> transposition_table;

};



#endif