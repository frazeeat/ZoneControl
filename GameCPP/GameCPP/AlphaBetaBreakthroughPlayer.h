#ifndef __CSE486AIProject__AlphaBetaBreakthroughPlayer__
#define __CSE486AIProject__AlphaBetaBreakthroughPlayer__

#include "GamePlayer.h"
#include "GameMove.h"
#include "BreakthroughState.h"
#include "BreakthroughMove.h"
#include <stdio.h>

class AlphaBetaBreakthroughPlayer : public GamePlayer {
public:
	AlphaBetaBreakthroughPlayer(std::string nickname);

	GameMove *getMove(GameState &state,
		const std::string &lastMv) override;
private:
};

#endif