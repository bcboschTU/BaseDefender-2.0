//
//  Enemie.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Enemie.h"

Enemie::Enemie(std::string _name,
               int _hp,
               float _xPos,
               float _yPos,
               float _width,
               float _height,
               float _angle,
               int _level){
    name = _name;
    hp = _hp;
    xPos = _xPos;
    yPos = _yPos;
    width = _width;
    height = _height;
    level = _level;
    
    nextXpos = _xPos;
    nextYpos = _yPos;
    
    dmg = 10;
    
    //movement:
    agility = 0.3;
    movementSpeed = 0;
    movementXdir = 0;
    movementYdir = 0;
    maxSpeed = 12;
    acceleration = 1.5;
    deceleration = 0.5;
    
    //target
    targetType = -1;
    
}

Mesh Enemie::getMesh(){
    return mesh;
}

void Enemie::setMesh(Mesh _mesh){
    mesh = _mesh;
}

void Enemie::updateEnemie(){
    calculateNewPos();
    if(nextXpos == getXPos() && nextYpos == getYPos() && movementSpeed >= 0){
        movementSpeed -= deceleration;
    }
    if((nextXpos != getXPos() || nextYpos != getYPos()) &&  movementSpeed < maxSpeed){
        movementSpeed += acceleration;
    }
    if (movementSpeed < 0) {
        movementXdir = 0;
        movementYdir = 0;
    }
    
    if(movementXdir == 0 && movementYdir == 0){
        float xDif = nextXpos - getXPos();
        float yDif = nextYpos - getYPos();
        movementXdir = xDif;
        movementYdir = yDif;
    }
    else{
        float xDif = nextXpos - getXPos();
        float yDif = nextYpos - getYPos();
        movementXdir = movementXdir * (1-agility) + (xDif * agility);
        movementYdir = movementYdir * (1-agility) + (yDif * agility);;
    }
    
    nextXpos = getXPos() + movementXdir * (movementSpeed);
    nextYpos = getYPos() + movementYdir * (movementSpeed);
    
    setXPos(nextXpos);
    setYPos(nextYpos);
    
    updateModelMatrix(nextXpos, nextYpos,getAngle() -90);
}


int Enemie::gotHit(std::vector<Bullet*> bullets){
    int hitReturn = -1;
    for (int i = 0; i< bullets.size(); i++) {
        Bullet* bullet = bullets[i];
        float distance = calculateDistance(xPos, bullet->getXPos(), yPos, bullet->getYPos());
        float hitDistance = width + bullet->getWidth();
        if(distance < hitDistance){
            hp = hp - bullet->getDmg();
            movementSpeed = 0;
            //bullet set on destroyed;
            bullet->setDestroyed(true);
            hitReturn = i;
        }
    }
    return hitReturn;
}

void Enemie::setTargetPlayer(Player *_target){
    targetType =1 ;
    targetPlayer = _target;
}
void Enemie::setTargetBase(Base *_target){
    targetType = 2;
    targetBase = _target;
}

void Enemie::calculateNewPos(){
    // Compute time difference between current and last frame
    if (targetType != -1) {
        
        switch (targetType) {
            case 1:
                calculateNewPosPlayer();
                break;
            case 2:
                calculateNewPosBase();
                break;
            default:
                break;
        }
    }
}

void Enemie::calculateNewPosPlayer(){
    nextXpos = targetPlayer->getXPos();
    nextYpos = targetPlayer->getYPos();
    
    //normalise next pos
    float xdif = getXPos() - targetPlayer->getXPos();
    float ydif = getYPos() - targetPlayer->getYPos();
    
    float angle = (atan2(ydif, xdif) * 180.0 / PI) + 180;
    setAngle(angle);
    
    calculateNewPosFinal(angle);
}

void Enemie::calculateNewPosBase(){
    nextXpos = targetBase->getXPos();
    nextYpos = targetBase->getYPos();
    
    //normalise next pos
    float xdif = getXPos() - targetBase->getXPos();
    float ydif = getYPos() - targetBase->getYPos();
    
    float angle = (atan2(ydif, xdif) * 180.0 / PI) + 180;
    
    calculateNewPosFinal(angle);
}

void Enemie::calculateNewPosFinal(float angle){
    nextXpos = getXPos() + cosf(angle * PI/180)  * 0.02;
    nextYpos = getYPos() + sinf(angle * PI/180)  * 0.02;
}


std::string Enemie::getName(){
    return name;
}
void Enemie::setName(std::string _name){
    name = _name;
}
int Enemie::getHp(){
    return hp;
}
void Enemie::setHp(int _hp){
    hp = _hp;
}
float Enemie::getXPos(){
    return xPos;
}
void Enemie::setXPos(float _xPos){
    xPos = _xPos;
}
float Enemie::getYPos(){
    return yPos;
}
void Enemie::setYPos(float _yPos){
    yPos = _yPos;
}
float Enemie::getWidth(){
    return width;
}
void Enemie::setWidth(float _width){
    width = _width;
}
float Enemie::getHeight(){
    return height;
}
void Enemie::setHeight(float _height){
    height = _height;
}
float Enemie::getAngle(){
    return angle;
}
void Enemie::setAngle(float _angle){
    angle = _angle;
}
int Enemie::getLevel(){
    return level;
}
void Enemie::setLevel(int _level){
    level = _level;
}

int Enemie::getDmg(){
    return dmg;
}
void Enemie::setDmg(int _dmg){
    dmg = _dmg;
}

float Enemie::calculateDistance(float x1, float x2, float y1, float y2){
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
}

void Enemie::updateModelMatrix(float _xpos, float _ypos, float _rot){
    Mesh meshTemp;
    glm::vec3 temp = glm::vec3(_xpos,_ypos, -200);
    meshTemp.translate(temp);
    _rot = _rot /180 *PI;
    meshTemp.rotate(glm::vec3(0.f, 0.f, 1.f), _rot);
    meshTemp.scale(glm::vec3(width, height, 0.5*(width+height)));
    mesh = meshTemp;
    
}
