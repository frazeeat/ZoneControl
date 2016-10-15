//
//  DoublePosBoardGameMove.h
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/5/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#ifndef __CSE486AIProject__DoublePosBoardGameMove__
#define __CSE486AIProject__DoublePosBoardGameMove__

#include "BoardGameMove.h"
#include <vector>

class DoublePosBoardGameMove : public BoardGameMove {
public:
    
    inline DoublePosBoardGameMove() : BoardGameMove(2) {}
    
    inline DoublePosBoardGameMove(int r1, int c1, int r2, int c2)
            : BoardGameMove(std::vector<int>{r1, c1, r2, c2}) {}
    
    inline int row1() const { return coordinates[0]; }
    
    inline int col1() const { return coordinates[1]; }
    
    inline int row2() const { return coordinates[2]; }
    
    inline int col2() const { return coordinates[3]; }
    
    inline void setMv(int r1, int c1, int r2, int c2) {
        coordinates[0] = r1;
        coordinates[1] = c1;
        coordinates[2] = r2;
        coordinates[3] = c2;
    }
    
    inline void setMv(const DoublePosBoardGameMove &mv) {
        coordinates[0] = mv.row1();
        coordinates[1] = mv.col1();
        coordinates[2] = mv.row2();
        coordinates[3] = mv.col2();
    }
};

#endif /* defined(__CSE486AIProject__DoublePosBoardGameMove__) */
