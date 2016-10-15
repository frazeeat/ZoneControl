//
//  ClobberState.cpp
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/5/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//


#include "ClobberState.h"
#include <cstdlib>
#include <algorithm>

GameState* ClobberState::create() {
    return new ClobberState();
}

Params& ClobberState::getClobberParams() {
    static Params *clobberParams = new Params(std::string("config")
                                    + Params::separatorChar + "clobber.txt");
    return *clobberParams;
}

ClobberState::ClobberState() : BoardGameState
    (getClobberParams().intValue("ROWS"),
     getClobberParams().intValue("COLS"),
     getClobberParams().charValue("HOMESYM"),
     getClobberParams().charValue("AWAYSYM"),
     getClobberParams().charValue("EMPTYSYM")) {}

bool ClobberState::moveOK(const GameMove &gm) const {
    const ClobberMove mv = static_cast<const ClobberMove&>(gm);
    int rowDiff = mv.getRowI(0) - mv.getRowI(1);
    int colDiff = mv.getColI(0) - mv.getColI(1);
    if (getStatus()==Status::GAME_ON && posOK(mv.row1(), mv.col1())
        && posOK(mv.row2(), mv.col2()) &&
        board[mv.row1()*COLS+mv.col1()] == getCurPlayerSym() &&
        board[mv.row2()*COLS+mv.col2()] == getCurOpponentSym() &&
        ((rowDiff == 0 && std::abs(colDiff) == 1) ||
         (std::abs(rowDiff) == 1 && colDiff == 0)))
        return true;
    return false;
}

void ClobberState::thisGameMakeMove(const GameMove &gm) {
    const ClobberMove &mv = static_cast<const ClobberMove&>(gm);
    board[mv.row1()*COLS+mv.col1()] = EMPTYSYM;
    board[mv.row2()*COLS+mv.col2()] = getCurPlayerSym();
}

Status ClobberState::thisGameCheckTerminalUpdateStatus() {
    int index = -1;
    if (getWho() == Who::HOME) {
        return std::any_of(board.begin(), board.end(),
            [&](char &ch) {index++; return ch == HOMESYM &&
            ((index%COLS != COLS-1 && board[index+1] == AWAYSYM)       //right
             ||(index/COLS != ROWS-1 && board[index+COLS] == AWAYSYM)  //down
             ||(index%COLS != 0 && board[index-1] == AWAYSYM)          //left
             ||(index/COLS != 0 && board[index-COLS] == AWAYSYM));})   //up
            ? Status::GAME_ON : Status::AWAY_WIN;
    } else {
        return std::any_of(board.begin(), board.end(),
            [&](char &ch) {index++; return ch == AWAYSYM &&
            ((index%COLS != COLS-1 && board[index+1] == HOMESYM)       //right
             ||(index/COLS != ROWS-1 && board[index+COLS] == HOMESYM)  //down
             ||(index%COLS != 0 && board[index-1] == HOMESYM)          //left
             ||(index/COLS != 0 && board[index-COLS] == HOMESYM));})   //up
            ? Status::GAME_ON : Status::HOME_WIN;
    }
}

