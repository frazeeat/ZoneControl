//
//  GamePlayer.cpp
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 5/27/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#include "GamePlayer.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <thread>
#include <chrono>


Params& GamePlayer::tournamentParams() {
    static Params* tournamentParams = new Params(std::string("config")
                                    + Params::separatorChar + "tournament.txt");
    return *tournamentParams;
}


GamePlayer::GamePlayer(std::string nickNm, std::string gameName) {
    std::vector<char> replaceCharList = {':', '/', '\\', '*', '?',
                                         '"', '<', '>', '|'};
	std::replace_if(nickNm.begin(), nickNm.end(),
        [&](const char &c) {return std::find(replaceCharList.begin(),
            replaceCharList.end(), c) != replaceCharList.end();}, ';');
    nickname = nickNm;
    side = Who::HOME;
    st = GameStateFactory::createGameState(gameName);
    client = TCPClient();
}

void GamePlayer::compete(int argc, char* args[], int dumpLevel) {
	std::string host = "www.frazee-family.com";//tournamentParams().stringValue("HOST");
    int port = (argc == 1) ? tournamentParams().intValue("PORT")
             : std::atoi(args[1]);
    if (!client.create(host, port)) {
        std::perror(std::string("Error connecting to " + host + ":"
                                + std::to_string(port)).c_str());
        std::cout << nickname << " tournament over" << std::endl;
        return;
    }
    std::cout << "Connected to server, now waiting to play" << std::endl;
    
    init();
    client.sendMsg(nickname);
    
    while (true) {
        //std::this_thread::sleep_for(std::chrono::microseconds(200));
        std::string cmd = client.receiveMsg();
        if (cmd == "DONE") {
            if (dumpLevel > 0)
                std::cout << nickname << " is done playing" << std::endl;
            done();
            break;
        } else if (cmd == "START") {
            side = GameState::str2who(client.receiveMsg());
            std::string opp = client.receiveMsg();
            if (dumpLevel > 0)
				std::cout << nickname << " new game as " << GameState::who2str(side)
						<< " against " << opp << std::endl;
            std::string msgForOpp = messageForOpponent(opp);
            if (dumpLevel > 0)
                std::cout << "Message for opponent: "
                << msgForOpp << std::endl;
            client.sendMsg(msgForOpp);
            std::string msgFromOpp = client.receiveMsg();
            messageFromOpponent(msgFromOpp);
            if (dumpLevel > 0)
                std::cout << "Message from opponent: "
                << msgFromOpp << std::endl;
            startGame(opp);
        } else if (cmd == "OVER") {
            std::string winner = client.receiveMsg();
            client.sendMsg("OVER");
            if (winner == "DRAW") {
                if (dumpLevel > 0)
                    std::cout << "I (" << nickname << " had a draw";
                endGame(0);
            } else if (st->str2who(winner) == side) {
                if (dumpLevel > 0)
                    std::cout << "I (" << nickname << ") won" << std::endl;
                endGame(+1);
            } else {
                if (dumpLevel > 0)
                    std::cout << "I (" << nickname << ") lost" << std::endl;
                endGame(-1);
            }
        } else if (cmd == "MOVE") {
            std::string lastMove = client.receiveMsg();
            std::string boardStr = client.receiveMsg();
            st->parseMsg(boardStr);
            
            if (dumpLevel > 1) {
                std::cout << "Turn " << nickname << " "
                << GameState::who2str(side) << std::endl
                << "Last move: " << lastMove << std::endl
                << "Current state\n" << st->toDisplayStr();
            }
            GameMove *mv = getMove(*st, lastMove);
            std::string mvStr = mv->toString();
            if (dumpLevel > 1)
                std::cout << "Send my move: " << mvStr <<std::endl;
            client.sendMsg(mvStr);
            delete mv;
            std::string timeStr = client.receiveMsg();	// should be "TIME"
            if (timeStr != "TIME")
                std::perror(std::string("time message:" + timeStr).c_str());
            double time = std::stod(client.receiveMsg());
            if (dumpLevel > 1)
                std::cout << time << " seconds" << std::endl;
            timeOfLastMove(time);
        } else {
            std::perror(std::string("bad command from server: "
                                    + cmd).c_str());
            std::exit(EXIT_FAILURE);
        }
    }
}
