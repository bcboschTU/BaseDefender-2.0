//
//  GameState.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "GameState.h"


GameState::GameState(){
    gameState = MENU;
}
void GameState::setGameState(int i){
    gameState = GameStateType(i);
}

GameStateType GameState::getGameState(){
    return gameState;
}