//
//  BoardGameState.h
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/4/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#ifndef __CSE486AIProject__BoardGameState__
#define __CSE486AIProject__BoardGameState__

#include "GameState.h"
#include "BoardGameMove.h"

class BoardGameState : public GameState {
    
public:
    
    //-------------------------------------------------------------
    //------------------ BOARD GAME PARAMETERS --------------------
    //-------------------------------------------------------------
    
    const int ROWS;
    const int COLS;
    const char HOMESYM;
    const char AWAYSYM;
    const char EMPTYSYM;
    
    //-------------------------------------------------------------
    //---------------- BOARD GAME ACCESS METHODS ------------------
    //-------------------------------------------------------------
    
    BoardGameState(const BoardGameState& other);
    
    BoardGameState(BoardGameState &&other);
    
    BoardGameState& operator = (const BoardGameState &other);
    
    BoardGameState& operator = (BoardGameState &&other);
    
    /**
     * check if a position is valid on the board
     * @param r the row
     * @param c the column
     * @return true if it is valid, false otherwise
     */
    bool posOK(int r, int c) const;
    
    /**
     * get the symbol representing the current turn player
     * @return the char of the current turn player, i.e. HOMESYM if 
     *         current side is HOME, AWAYSYM otherwise
     */
    char getCurPlayerSym() const;
    
    /**
     * get the symbol representing the current turn player's opponent
     * @return the char of the current turn player's opponent, i.e. 
     *         AWAYSYM if current side is HOME, HOMESYM otherwise
     */
    char getCurOpponentSym() const;
    
    const std::vector<char>* getBoard1D() const;
    
    /**
     * Another way of getting the cell by giving the row and col
     * @param row the row
     * @param col the column
     * @return the char of that coordinate
     */
    char getCell(int row, int col) const;
    
    /**
     * Another way of setting the cell by giving the row and col
     * @param row the row
     * @param col the column
     * @param c the char to replace to
     */
    void setCell(int row, int col, char c);
    
    /**
     * Destructor.
     */
    inline virtual ~BoardGameState() {}
    
private:
    
    void thisGameReset() override;
    
    void thisGameParseMsg(const std::string &s) override;
    
    std::string thisGameMsg() override;
    
    std::string thisGameToDisplayStr() override;
    
protected:
    std::vector<char> board;
    
    //std::vector<std::vector<char>> board2D;

    BoardGameState(int rows, int cols, char homeSym,
                   char awaySym, char emptySym);
};


#endif /* defined(__CSE486AIProject__BoardGameState__) */
