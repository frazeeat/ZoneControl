//
//  GameState.h
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 5/26/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#ifndef __CSE486AIProject__GameState__
#define __CSE486AIProject__GameState__

#include "GameMove.h"
#include "Params.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>


enum class Status {
    GAME_ON,
    HOME_WIN,
    AWAY_WIN,
    DRAW
};

enum class Who {
    HOME,
    AWAY
};


class GameState {
public:
    
    //-------------------------------------------------------------
    //------------------------- GETTERS ---------------------------
    //-------------------------------------------------------------
    
    /**
     * Get number of moves played.
     * @return number of moves played
     */
    int getNumMoves() const;
    
    /**
     * Whose turn is next
     * @return side that gets to move next
     */
    Who getWho() const;
    
    /**
     * Retrieve status of game
     * @return game status
     */
    Status getStatus() const;
    
    
    //-------------------------------------------------------------
    //-------------------- GAMEPLAY METHODS -----------------------
    //-------------------------------------------------------------

    /**
     * Toggle the player to its opponent's turn
     */
    void togglePlayer();

    /**
     * Reset the game to its initial condition
     */
    virtual void reset() final;
    
    /**
     * Determines if a particular move is legal, given the current
     * state configuration.
     * @param mv Move to be made
     * @return true if the move is valid
     */
    virtual bool moveOK(const GameMove &gm) const = 0;
    
    /**
     * Updates the game based on a particular move.
     * @param mv Move to be made
     * @param checkValidMove is going to check if this move is valid.
     *        default is true. 
     *        NOTE: MAKE IT FALSE ONLY WHEN YOU KNOW THIS MOVE IS VALID
     *              TO SPEED IT UP BY NOT CHECKING IT. OTHERWISE INVALID 
     *              MOVE COULD POTENTIALLY CRASH THE PROGRAM.
     * @param checkTerminal being true will check whether the game
     *        reaches a terminal condition(DRAW, HOME_WIN or AWAYWIN), 
     *        and update the status correspondingly if so. default is true.
     *        NOTE: Make it false to boost performance by
     *              not checking the terminal condition & update status.
     *              DO SO ONLY WHEN YOU ARE CERTAIN IT WILL NOT REACH TERMINAL
     *              OR YOU WILL CHECK AND UPDATE THE STATUS LATER BY CALLING
     *              checkTerminalUpdateStatus()
     * @return true if move was successfully performed
     */
    virtual bool makeMove(const GameMove &gm, bool checkValidMove = true,
                          bool checkTerminal = true) final;
    
    /**
     * check if the game reaches terminal and update the status correspondingly
     * @return true if it is terminal, i.e. DRAW, HOME_WIN or AWAY_WIN.
     */
    virtual bool checkTerminalUpdateStatus() final;
    
    /**
     * Convert to a string for display usage.
     * @return string representation of the State, suitable for display
     */
    virtual std::string toDisplayStr() final;
    
    
    //-------------------------------------------------------------
    //--- NETWORK & MAINTANENCE METHODS, YOU DON'T NEED TO USE ----
    //-------------------------------------------------------------
    
    /**
     * Convert a string to its corresponding enum Who
     * @param sideStr string of a enum who
     * @return Enum Who representation of that string
     */
    static Who str2who(const std::string &sideStr);
    
    /**
     * Convert a enum Who to its corresponding string
     * @param who the enum who
     * @return the string representation of enum who
     */
    static std::string who2str(Who who);
    
    /**
     * Takes a message suffix and parses out the information common to
     * all GameStates.
     * @param suffix String suffix. Lookes like: "[HOME 12 GAME_ON]"
     */
    virtual void parseMsg(const std::string &s) final;
    
    /**
     * Creates a message suffix for this particular game state.
     * @return String suffix for communication to/from server.
     */
    virtual std::string constructMsg() final;
    
    /**
     * Destructor.
     */
    inline virtual ~GameState() {}
    
protected:
    GameState();
    
private:
    Status status;			// status of current game
    Who who;				// side that has next move
    int numMoves;
    
    //static const std::unordered_map<std::string, GameState*> gameStatePool;
    
    // string representation of the status
    static const std::vector<std::string> statusStrVec;
    
    // string representation of the sides
    static const std::vector<std::string> sidesStrVec;
    
    // Converts a string into its Status type
    static Status parseStatus(const std::string &str);
    
    // Initialize the state
    void initState();
    
    void parseMsgSuffix(const std::string &suffix);
    
    std::string msgSuffix();
    
    /**
     * Sets the specific game back to its beginning state.
     */
    virtual void thisGameReset() = 0;
    
    /**
     * Updates the game based on a particular move
     * @param mv Move to be made
     */
    virtual void thisGameMakeMove(const GameMove &gm) = 0;
    
    virtual Status thisGameCheckTerminalUpdateStatus() = 0;
    
    /**
     * Recreates the game's state from a string representation.
     * In particular, the string is a string generated as a "message" string 
     * (i.e., one without newlines). This method must be able to fill in the 
     * specific game representing variable, i.e. board info for board game, 
     * card and deck for card game, etc.
     * @param s Message string representation of the specific game state.
     */
    virtual void thisGameParseMsg(const std::string &s) = 0;
    
    /**
     * Convert to a string suitable for tournament (i.e., no newlines)
     * @return String representation of the State, suitable for tournament
     * communication.
     */
    virtual std::string thisGameMsg() = 0;
    
    virtual std::string thisGameToDisplayStr() = 0;
};



#endif /* defined(__CSE486AIProject__GameState__) */
