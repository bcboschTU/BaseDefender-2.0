//
//  GameState.h
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__GameState__
#define __BaseDefender__GameState__

#include <stdio.h>

enum GameStateType{
    MENU = 0,
    GAME = 1,
    BUYTIME = 2
};

class GameState{
public:
    GameState();
    void setGameState(int i);
    GameStateType getGameState();
private:
    GameStateType gameState;
};

#endif /* defined(__BaseDefender__GameState__) */
