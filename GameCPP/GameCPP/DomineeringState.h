//
//  DomineeringState.h
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 5/29/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#ifndef __CSE486AIProject__DomineeringState__
#define __CSE486AIProject__DomineeringState__

#include "Params.h"
#include "BoardGameState.h"
#include "DomineeringMove.h"
#include <stdio.h>
#include <vector>

class DomineeringState : public BoardGameState {
public:
    
    static Params& getDomineeringParams();
    
    static GameState* create();
    
    bool moveOK(const GameMove &gm) const override;
    
	DomineeringState();

private:
        
    void thisGameMakeMove(const GameMove &gm) override;
    
    Status thisGameCheckTerminalUpdateStatus() override;

};


#endif /* defined(__CSE486AIProject__DomineeringState__) */
