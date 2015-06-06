//
//  Player.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Player.h"

Player::Player(std::string _name,
               int _hp,
               float _xPos,
               float _yPos,
               float _width,
               float _height,
               float _angle,
               int _level):GameObject(_name,_hp,_xPos,_yPos,_width,_height,_angle,_level){
    fireRatePrimary = 0.1;
    fireRateSecondary = 0.1;
    primaryWeaponType = NORMAL;
    secondaryWeaponType = NUKE;
    lastTimePrimary = glfwGetTime();
    lastTimeSecondary = glfwGetTime();
    agility = 0.05;
    movementSpeed = 0;
    movementXdir = 0;
    movementYdir = 0;
    nextXpos = _xPos;
    nextYpos = _yPos;
    
}

Mesh Player::getMesh(){
    return mesh;
}
void Player::setMesh(Mesh _mesh){
    mesh = _mesh;
}


void Player::updatePlayer(){
    if(nextXpos == getXPos() && nextYpos == getYPos() && movementSpeed >= 0){
        movementSpeed -= 0.01;
    }
    if((nextXpos != getXPos() || nextYpos != getYPos()) &&  movementSpeed < 1.5){
        movementSpeed += 0.15;
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
    
    updateModelMatrix(getXPos() - nextXpos,getYPos() - nextYpos);
    
    setXPos(nextXpos);
    setYPos(nextYpos);
    
    
}

void Player::shootPrimary(float dirXPos, float dirYPos){
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTimePrimary);
    
    if(deltaTime > fireRatePrimary){
        //calculate angle:
        float xdif = getXPos() - dirXPos;
        float ydif = getYPos() - dirYPos;
        
        float angle = (atan2(ydif, xdif) * 180.0 / PI) + 180;
        setAngle(angle);
        
        Bullet bullet = Bullet(getXPos(), getYPos(), angle, primaryWeaponType,getName());
        bullets.push_back(bullet);
        
        lastTimePrimary = currentTime;
    }
}

void Player::shootSecondary(float dirXPos, float dirYPos){
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTimeSecondary);
    
    if(deltaTime > fireRateSecondary){
        //calculate angle:
        float xdif = getXPos() - dirXPos;
        float ydif = getYPos() - dirYPos;
        
        float angle = (atan2(ydif, xdif) * 180.0 / PI) + 180;
        setAngle(angle);
        
        Bullet bullet = Bullet(getXPos(), getYPos(), angle, secondaryWeaponType,getName());
        bullets.push_back(bullet);
        
        lastTimeSecondary = currentTime;
    }
}

void Player::updateAngleMousePos(float dirXPos, float dirYPos){
    float xdif = getXPos() - dirXPos;
    float ydif = getYPos() - dirYPos;
    
    float angle = (atan2(ydif, xdif) * 180.0 / PI) + 180;
    setAngle(angle);
}

std::vector<Bullet> *Player::getBullets(){
    updateBullets();
    
    return &bullets;
}

float Player::getFireRatePrimary(){
    return fireRatePrimary;
}

float Player::getXPos(){
    return GameObject::getXPos();
}
float Player::getYPos(){
    return GameObject::getYPos();
}

int Player::getHp(){
    return GameObject::getHp();
}

void Player::setNewPos(float newXPos, float newYPos){
    nextXpos = newXPos;
    nextYpos = newYPos;
}

void Player::updateBullets(){
    for(int i = 0; i< bullets.size(); i++){
        Bullet *bullet = &bullets[i];
        bullet->updateBullet();
        if(bullet->getDestroyed()){
            removeBullet(i);
        }
        
    }
}

void Player::removeBullet(int index){
    bullets.erase(bullets.begin() + index);
}


bool Player::getHitByEnemie(float enemieXPos, float enemieYPos, float enemieWidth, int dmg){
    float distance = calculateDistance(getXPos(), enemieXPos, getYPos(), enemieYPos);
    float hitDistance = getWidth() + enemieWidth;
    if(distance < hitDistance){
        setHp(getHp()- dmg);
        return true;
    }
    return false;
}

void Player::updateModelMatrix(float _nextXpos, float _nextYpos){
    glm::vec3 temp = glm::vec3(_nextXpos,_nextYpos, 0);
    mesh.translate(temp);
}