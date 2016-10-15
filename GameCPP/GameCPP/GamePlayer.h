//
//  GamePlayer.h
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 5/27/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#ifndef __CSE486AIProject__GamePlayer__
#define __CSE486AIProject__GamePlayer__

#include "GameState.h"
#include "GameStateFactory.h"
#include "Params.h"
#include "Network.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

class GamePlayer {
public:
    
    /**
     * Produces the player's move, given the current state of the game.
     * This function must return a value within the time alloted by the
     * game timing parameters.
     * @param state Current state of the game
     * @param lastMv Opponent's last move. "--" if it is game's first move.
     * @return Player's move
     */
    virtual GameMove *getMove(GameState &state, const std::string &lastMv) = 0;
	virtual GameMove *getPuzzleMove(GameState &state)
	{
		return getMove(state, "--");
	}		// This could be overridden

	void solvePuzzles(std::vector<std::string> fnames)
	{
		init();
		for (std::string fname : fnames) {
			std::cout << "-------- " << fname << " --------" << std::endl;
			solvePuzzle(fname);
		}
	}
	void solvePuzzle(std::string fname)
	{
		try {
			std::fstream input(fname);
			std::string boardStr = "";
			while (!input.fail()) {
				const int N = 100;
				char buf[100];
				input.getline(buf, N);
				boardStr += buf;
			}
			input.close();

			st->parseMsg(boardStr);
			GameMove *move = getPuzzleMove(*st);
			std::cout << "Original board:" << std::endl;
			std::cout << st->toDisplayStr() << std::endl;
			std::cout << "Move: " << move->toString() << std::endl;
			st->makeMove(*move);
			std::cout << "Updated board:" << std::endl;
			std::cout << st->toDisplayStr() << std::endl;
		}
		catch (...) {
			std::cerr << "Problem solving puzzle " << std::endl;
			exit(0);
		}
	}

    inline Who getSide() const {return side;}
    
    inline std::string getNickname() const {return nickname;}
    
    inline const GameState* getGameState() const {return st;}
    
    /**
     * Initializes the player at the beginning of the tournament. This is called
     * once, before any games are played. This function must return within
     * the time alloted by the game timing parameters. Default behavior is
     * to do nothing.
     */
    inline void init() { }
    
    /**
     * This is called to register the opponent's message to this player.
     * This is called after getMessageForOpponent
     * @param msg Message sent by opposing player
     */
    inline void messageFromOpponent(const std::string &msg) { }
    
    /**
     * This is called to obtain the string this player wants to send
     * to its opponent.	This is called before getMessageFromOpponent
     * @return The string to be sent to the opponent
     * @param opponent Name of the opponent being played
     */
    inline std::string messageForOpponent(const std::string &opponentName)
    { return "hello"; }
    
    /**
     * This is called at the start of a new game. This should be relatively
     * fast, as the player must be ready to respond to a move request, which
     * should come shortly thereafter. Default behavior is to do nothing.
     * @param opponent Name of the opponent being played
     */
    inline void startGame(std::string opponentName) { }
    
    /**
     * Called to inform the player how long the last move took. This can
     * be used to calibrate the player's search depth. Default behavior is
     * to do nothing.
     * @param secs Time for the server to receive the last move
     */
    inline void timeOfLastMove(double secs) { }
    
    /**
     * Called when the game has ended. Default behavior is to do nothing.
     * @param result -1 if loss, 0 if draw, +1 if
     */
    inline void endGame(int result) { }
    
    /**
     * Called at the end of the tournament. Can be used to do
     * housekeeping tasks. Default behavior is to do nothing.
     */
    inline void done() { }
    
    /**
     * Used to compete the player in a tournament.
     * @param args command line arguments passed to the GamePlayer
     * @param dumpLevel 0, 1, 2 indicating how much info to display to console.
     *        Default is 2.
     */
    void compete(int argc, char* args[], int dumpLevel = 2);
    
    virtual ~GamePlayer() {delete st;}

protected:
    /**
     * Constructs a game player
     * @param nickname Mascot name of team
     * @param isDeterministic true if player is completely deterministic
     */
    GamePlayer(std::string nickname, std::string gameName);
    
private:
    static Params& tournamentParams();
    
    GameState *st;
    TCPClient client;
    Who side;
    std::string nickname;
};
    
#endif /* defined(__CSE486AIProject__GamePlayer__) */
