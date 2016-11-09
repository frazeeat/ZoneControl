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
	int DepthLimit = 5;
#define MAX_DEPTH_LIMIT 10
	ScoredBreakthroughMove mvStack[MAX_DEPTH_LIMIT];

};



#endif