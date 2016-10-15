//
//  DomineeringState.cpp
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 5/29/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#include "DomineeringState.h"
#include <cstdlib>
#include <algorithm>


GameState* DomineeringState::create() {
    return new DomineeringState();
}

Params& DomineeringState::getDomineeringParams() {
    static Params* domineeringPrms = new Params(std::string("config") + Params::separatorChar + "domineering.txt");
    return *domineeringPrms;
}

DomineeringState::DomineeringState() : BoardGameState
    (getDomineeringParams().intValue("ROWS"),
     getDomineeringParams().intValue("COLS"),
     getDomineeringParams().charValue("HOMESYM"),
     getDomineeringParams().charValue("AWAYSYM"),
     getDomineeringParams().charValue("EMPTYSYM")) {}

bool DomineeringState::moveOK(const GameMove &gm) const {
    const DomineeringMove mv = static_cast<const DomineeringMove&>(gm);
    int rowDiff = mv.row1() - mv.row2();
    int colDiff = mv.col1() - mv.col2();
    if (getStatus()==Status::GAME_ON && posOK(mv.row1(), mv.col1())
        && posOK(mv.row2(), mv.col2()) &&
        board[mv.row1()*COLS+mv.col1()] == EMPTYSYM &&
        board[mv.row2()*COLS+mv.col2()] == EMPTYSYM &&
        ((getWho() == Who::HOME && rowDiff == 0 && std::abs(colDiff) == 1)||
         (getWho() == Who::AWAY && std::abs(rowDiff) == 1 && colDiff == 0)))
            return true;
    return false;
}

void DomineeringState::thisGameMakeMove(const GameMove &gm) {
    const DomineeringMove &mv = static_cast<const DomineeringMove&>(gm);
    char playerSymbol = getWho() == Who::HOME ? HOMESYM : AWAYSYM;
    board[mv.row1()*COLS+mv.col1()] = playerSymbol;
    board[mv.row2()*COLS+mv.col2()] = playerSymbol;
}

Status DomineeringState::thisGameCheckTerminalUpdateStatus() {
    if (getWho() == Who::HOME) {
        int c = -1;
        return std::any_of(board.begin(), board.end(), [&](const char &ch) {
            c = c == 8 ? 0 : c+1;
            return ch == EMPTYSYM && c+1 != COLS && *(&ch+1) == EMPTYSYM;
        }) ? Status::GAME_ON : Status::AWAY_WIN;
    } else {
        return std::any_of(board.begin(), board.end(), [&](char &ch) {
            return ch == EMPTYSYM && &ch - board.data() + COLS <= ROWS*COLS
                   && *(&ch+COLS) == EMPTYSYM;
        }) ? Status::GAME_ON : Status::HOME_WIN;
    }
}



