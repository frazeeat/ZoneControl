#ifndef __CSE486AIProject__AlphaBetaBreakthroughPlayer__
#define __CSE486AIProject__AlphaBetaBreakthroughPlayer__

#include "GamePlayer.h"
#include "GameMove.h"
#include "BreakthroughState.h"
#include "BreakthroughMove.h"
#include <stdio.h>
#include "ScoredBreakthroughMove.h"
class AlphaBetaBreakthroughPlayer : public GamePlayer {
public:
	AlphaBetaBreakthroughPlayer(std::string nickname);

	GameMove *getMove(GameState &state,
		const std::string &lastMv) override;
private:
	void alphaBeta(BreakthroughState brd, int currDepth,
		double alpha, double beta);
	boolean terminalValue(GameState &brd, ScoredBreakthroughMove mv);
#define DepthLimit 5
	ScoredBreakthroughMove mvStack[DepthLimit];


};



#endif