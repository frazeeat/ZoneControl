//
//  BoardGameState.cpp
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/4/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#include "BoardGameState.h"
#include <algorithm>

BoardGameState::BoardGameState(const BoardGameState& other) : ROWS(other.ROWS),
    COLS(other.COLS), HOMESYM(other.HOMESYM), AWAYSYM(other.AWAYSYM),
    EMPTYSYM(other.EMPTYSYM), board(other.board), GameState(other) {}

BoardGameState::BoardGameState(BoardGameState &&other) : ROWS(other.ROWS),
    COLS(other.COLS), HOMESYM(other.HOMESYM), AWAYSYM(other.AWAYSYM),
    EMPTYSYM(other.EMPTYSYM), board(other.board), GameState(std::move(other)) {}

BoardGameState& BoardGameState::operator = (const BoardGameState &other) {
    if (this != &other) {
        GameState::operator=(other);
        board = other.board;
    }
    return *this;
}

BoardGameState& BoardGameState::operator = (BoardGameState &&other) {
    GameState::operator=(std::move(other));
    board = std::move(other.board);
    return *this;
}


bool BoardGameState::posOK(int r, int c) const {
    return r >= 0 && r < ROWS && c >= 0 && c < COLS;
}

BoardGameState::BoardGameState(int rows, int cols, char homeSym, char awaySym,
    char emptySym) : ROWS(rows), COLS(cols), HOMESYM(homeSym), AWAYSYM(awaySym),
                     EMPTYSYM(emptySym), board(std::vector<char>(rows*cols)) {
    thisGameReset();
}

char BoardGameState::getCurPlayerSym() const {
    return (getWho() == Who::HOME) ? HOMESYM : AWAYSYM;
}

char BoardGameState::getCurOpponentSym() const {
    return (getWho() == Who::HOME) ? AWAYSYM : HOMESYM;
}

const std::vector<char>* BoardGameState::getBoard1D() const {
    return &board;
}

char BoardGameState::getCell(int row, int col) const {
    return board[row*COLS + col];
}

void BoardGameState::setCell(int row, int col, char c) {
    board[row*COLS + col] = c;
}

void BoardGameState::thisGameReset() {
    std::fill(board.begin(), board.end(), EMPTYSYM);
}

void BoardGameState::thisGameParseMsg(const std::string &s) {
	std::vector<char>::iterator bi = board.begin() + (ROWS - 1)*COLS;
	std::string::const_iterator si = s.begin();
	for (int r = 0; r < ROWS; r++) {
		int logicalRow = ROWS - 1 - r;
		std::copy_n(s.begin() + r*COLS, COLS, board.begin() + logicalRow*COLS);
	}
}

std::string BoardGameState::thisGameMsg() {
	std::string boardStr;
	for (int r = 0; r < ROWS; r++) {
		int logicalRow = ROWS - 1 - r;
		std::copy_n(board.begin() + logicalRow*COLS, COLS, std::back_inserter(boardStr));
	}
	return boardStr;
}

std::string BoardGameState::thisGameToDisplayStr() {
	std::string boardStr;
	for (int r = 0; r < ROWS; r++) {
		int logicalRow = ROWS - 1 - r;
		std::copy_n(board.begin() + logicalRow*COLS, COLS, std::back_inserter(boardStr));
		boardStr.append("\n");
	}
	return boardStr;
}




