//
//  Enemie.h
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__Enemie__
#define __BaseDefender__Enemie__

#include <stdio.h>
#include "Player.h"
#include "Base.h"

class Enemie{
public:
    Enemie(std::string _name,
           int _hp,
           float _xPos,
           float _yPos,
           float _width,
           float _height,
           float _angle,
           int _level);
    void draw();
    void updateEnemie();
    int gotHit(std::vector<Bullet*> bullets);
    void calculateNewPos();
    void calculateNewPosPlayer();
    void calculateNewPosBase();
    void calculateNewPosFinal(float angle);
    std::string getName();
    void setName(std::string _name);
    int getHp();
    void setHp(int hp);
    float getXPos();
    void setXPos(float _xPos);
    float getYPos();
    void setYPos(float _yPos);
    float getWidth();
    void setWidth(float _width);
    float getHeight();
    void setHeight(float _height);
    float getAngle();
    void setAngle(float _angle);
    int getLevel();
    void setLevel(int level);
    int getDmg();
    void setDmg(int _dmg);
    void setTargetPlayer(Player *_target);
    void setTargetBase(Base *_target);
    float calculateDistance(float x1, float x2, float y1, float y2);
private:
    std::string name;
    int hp;
    float xPos;
    float yPos;
    float width;
    float height;
    float angle;
    int level;
    
    //is enemie hits something, this dmg
    float dmg;
    
    int targetType;
    Player *targetPlayer;
    Base *targetBase;
    
    //movement
    float nextXpos;
    float nextYpos;
    float agility;
    float movementSpeed;
    float movementXdir;
    float movementYdir;
    float maxSpeed;
    float acceleration;
    float deceleration;
    
};


#endif /* defined(__BaseDefender__Enemie__) */
