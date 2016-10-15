//
//  GameStateFactory.cpp
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/6/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#include "GameStateFactory.h"
#include "DomineeringState.h"
#include "BreakthroughState.h"
#include "ClobberState.h"

//const std::unordered_map<std::string, gsCreateFn*>
//GameStateFactory::gameStatePool = {{"Domineering", &DomineeringState::create},
//                                   {"Clobber", &ClobberState::create}};
//
//GameState* GameStateFactory::createGameState(std::string gameName) {
//    auto it = gameStatePool.find(gameName);
//    return it == gameStatePool.end()
//           ? nullptr : gameStatePool.find(gameName)->second();
//}
//

GameState* GameStateFactory::createGameState(std::string gameName) {
	if (gameName == "Domineering")
		return DomineeringState::create();
	else if (gameName == "Breakthrough")
		return BreakthroughState::create();
	else
		return nullptr;
}