//
//  RandomBreakthroughPlayer.h
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/6/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#ifndef __CSE486AIProject__RandomBreakthroughPlayer__
#define __CSE486AIProject__RandomBreakthroughPlayer__

#include "GamePlayer.h"
#include "GameMove.h"
#include "BreakthroughState.h"
#include "BreakthroughMove.h"
#include <stdio.h>

class RandomBreakthroughPlayer : public GamePlayer {
public:
	RandomBreakthroughPlayer(std::string nickname);

	GameMove *getMove(GameState &state,
		const std::string &lastMv) override;
private:
};

#endif /* defined(__CSE486AIProject__RandomBreakthroughPlayer__) */
