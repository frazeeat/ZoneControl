//
//  RandomDomineeringPlayer.cpp
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/6/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#include "RandomDomineeringPlayer.h"
#include "DomineeringMove.h"
#include "DomineeringState.h"

RandomDomineeringPlayer::RandomDomineeringPlayer(std::string nickname)
    : GamePlayer(nickname, "Domineering") {}

GameMove* RandomDomineeringPlayer::getMove(GameState &state,
                                           const std::string &lastMv) {
    DomineeringState st = static_cast<DomineeringState&>(state);
    std::vector<DomineeringMove> mvArray;
    for (int r=0; r < st.ROWS; r++) {
        for (int c=0; c < st.COLS; c++) {
            DomineeringMove mv(r, c, r, c+1);
            if (state.moveOK(mv)) {
                mvArray.push_back(DomineeringMove(mv));
            }
            mv.setMv(r, c, r+1, c);
            if (state.moveOK(mv)) {
                mvArray.push_back(DomineeringMove(mv));
            }
        }
    }
    return new DomineeringMove(mvArray[rand()%mvArray.size()]);
}
