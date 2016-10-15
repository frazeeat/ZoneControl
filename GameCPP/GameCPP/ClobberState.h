//
//  ClobberState.h
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/5/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//


#ifndef __CSE486AIProject__ClobberState__
#define __CSE486AIProject__ClobberState__

#include <stdio.h>
#include "BoardGameState.h"
#include "Params.h"
#include "ClobberMove.h"

class ClobberState : public BoardGameState {
public:
    
    static Params& getClobberParams();
    
    static GameState* create();
    
    bool moveOK(const GameMove &gm) const override;
    
	ClobberState();

private:
    
    void thisGameMakeMove(const GameMove &gm) override;
    
    Status thisGameCheckTerminalUpdateStatus() override;
};

#endif /* defined(__CSE486AIProject__ClobberState__) */
