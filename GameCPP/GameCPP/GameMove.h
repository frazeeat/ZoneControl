//
//  GameMove.h
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 5/27/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#ifndef __CSE486AIProject__GameMove__
#define __CSE486AIProject__GameMove__

#include <stdio.h>
#include <string>

class GameMove {
public:
    /**
     * Converts a move to a string presentable to the console
     * @return String for human viewing or network communication.
     * The string can't contain newline characters.
     */
    virtual std::string toString() const = 0;
    
    /**
     * Converts a String (created by toString) into a GameMove.
     * @param s string to be parsed.
     */
    virtual void parseMove(const std::string s) = 0;
    
    virtual ~GameMove() {}
};


#endif /* defined(__CSE486AIProject__GameMove__) */
