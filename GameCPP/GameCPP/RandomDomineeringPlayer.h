//
//  RandomDomineeringPlayer.h
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/6/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#ifndef __CSE486AIProject__RandomDomineeringPlayer__
#define __CSE486AIProject__RandomDomineeringPlayer__

#include "GamePlayer.h"
#include "GameMove.h"
#include "DomineeringState.h"
#include "DomineeringMove.h"
#include <stdio.h>

class RandomDomineeringPlayer : public GamePlayer {
public:
    RandomDomineeringPlayer(std::string nickname);

	GameMove *getMove(GameState &state,
		const std::string &lastMv) override;
private:
};

#endif /* defined(__CSE486AIProject__RandomDomineeringPlayer__) */
