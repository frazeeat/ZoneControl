//
//  GameStateFactory.h
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/6/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#ifndef __CSE486AIProject__GameStateFactory__
#define __CSE486AIProject__GameStateFactory__

#include "GameState.h"
#include <stdio.h>
#include <string>

typedef GameState* gsCreateFn();

class GameStateFactory {
public:
    static GameState* createGameState(std::string gameName);
private:
    static const std::unordered_map<std::string, gsCreateFn*> gameStatePool;
};



#endif /* defined(__CSE486AIProject__GameStateFactory__) */
