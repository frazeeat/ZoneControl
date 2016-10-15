//
//  BoardGameMove.h
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/7/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#ifndef __CSE486AIProject__BoardGameMove__
#define __CSE486AIProject__BoardGameMove__

#include "GameMove.h"
#include <stdio.h>
#include <vector>
#include <string>

class BoardGameMove : public GameMove {
public:
    
    BoardGameMove();
    
    BoardGameMove(int numPoints);
    
    BoardGameMove(std::vector<int> pts);
    
    BoardGameMove(std::string s);
    
    int getRowI(int i) const;
    
    int getColI(int i) const;
    
    void setRowI(int i, int row);
    
    void setColI(int i, int col);
    
    int getNumCoordinates();
    
    std::string toString() const override;
    
    void parseMove(const std::string s) override;
    
protected:
    std::vector<int> coordinates;
};

#endif /* defined(__CSE486AIProject__BoardGameMove__) */
