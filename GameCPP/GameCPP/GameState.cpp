//
//  GameState.cpp
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 5/26/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#include "GameState.h"
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>


const std::vector<std::string> GameState::statusStrVec =
    {"GAME_ON", "HOME_WIN", "AWAY_WIN", "DRAW"};

const std::vector<std::string> GameState::sidesStrVec = {"HOME", "AWAY"};

Who GameState::str2who(const std::string &sideStr) {
    return static_cast<Who>(std::distance(sidesStrVec.begin(),
            std::find(sidesStrVec.begin(), sidesStrVec.end(), sideStr)));
}

std::string GameState::who2str(Who who) {
    return sidesStrVec[static_cast<int>(who)];
}

Status GameState::parseStatus(const std::string &statusStr) {
    return static_cast<Status>(std::distance(statusStrVec.begin(),
           std::find(statusStrVec.begin(), statusStrVec.end(), statusStr)));
}

int GameState::getNumMoves() const {
    return numMoves;
}

Who GameState::getWho() const {
    return who;
}

Status GameState::getStatus() const {
    return status;
}

void GameState::togglePlayer() {
    who = (who == Who::HOME) ? Who::AWAY : Who::HOME;
}

void GameState::reset() {
    initState();
    thisGameReset();
}

bool GameState::makeMove(const GameMove &gm, bool checkMove, bool checkTerm) {
    if (checkMove && !moveOK(gm))
        return false;
    numMoves++;
	thisGameMakeMove(gm);
	who = (who == Who::HOME) ? Who::AWAY : Who::HOME;
	if (checkTerm)
        checkTerminalUpdateStatus();
    return true;
}

bool GameState::checkTerminalUpdateStatus() {
    status = thisGameCheckTerminalUpdateStatus();
    return (status == Status::GAME_ON) ? false : true;
}


std::string GameState::toDisplayStr() {
	return  thisGameToDisplayStr() + '\n' + msgSuffix();
}

void GameState::parseMsg(const std::string &s) {
    parseMsgSuffix(s.substr(s.find('[')));
    thisGameParseMsg(s);
}

std::string GameState::constructMsg() {
    return msgSuffix() + thisGameMsg();
}


GameState::GameState() {
    initState();
}

void GameState::initState() {
    who = Who::HOME;
    numMoves = 0;
    status = Status::GAME_ON;
}

void GameState::parseMsgSuffix(const std::string &suffix) {
    std::istringstream suffixStream(suffix.substr(1, suffix.length() - 2));
    std::istream_iterator<std::string> suffixIt(suffixStream);
    who = str2who(*suffixIt++);
    numMoves = std::stoi(*suffixIt++);
    status = parseStatus(*suffixIt);
}

std::string GameState::msgSuffix() {
    return "[" + sidesStrVec[static_cast<int>(who)] + ' '
               + std::to_string(numMoves) + ' '
               + statusStrVec[static_cast<int>(status)] + "]";
}






