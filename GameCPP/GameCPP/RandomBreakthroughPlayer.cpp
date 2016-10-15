//
//  RandomDomineeringPlayer.cpp
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/6/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#include "RandomBreakthroughPlayer.h"
#include "BreakthroughMove.h"
#include "BreakthroughState.h"

RandomBreakthroughPlayer::RandomBreakthroughPlayer(std::string nickname)
    : GamePlayer(nickname, "Breakthrough") {}

GameMove* RandomBreakthroughPlayer::getMove(GameState &state,
                                           const std::string &lastMv) {
	BreakthroughState st = static_cast<BreakthroughState&>(state);
    std::vector<BreakthroughMove> mvArray;
    for (int r=0; r < st.ROWS; r++) {
        for (int c=0; c < st.COLS; c++) {
			int rowDelta = state.getWho() == Who::HOME ? +1 : -1;
			for (int dc = -1; dc <= +1; dc++) {
				BreakthroughMove mv(r, c, r + rowDelta, c + dc);
				if (state.moveOK(mv)) {
					mvArray.push_back(BreakthroughMove(mv));
				}
			}
        }
    }
	return new BreakthroughMove(mvArray[rand() % mvArray.size()]);
}
