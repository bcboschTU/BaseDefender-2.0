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
    secondaryWeaponType = EXPLOSIVE;
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
    
    setXPos(nextXpos);
    setYPos(nextYpos);
    
    updateModelMatrix(nextXpos, nextYpos,getAngle());
}

void Player::shootPrimary(float dirXPos, float dirYPos){
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTimePrimary);
    
    if(deltaTime > fireRatePrimary){
        //calculate angle:
        //float xdif = getXPos() - (dirYPos*1000);
        //float ydif = getYPos() - (dirYPos*1000);
        
        //float angle = (atan2(ydif, xdif) * 180.0 / PI) + 90;
        //setAngle(angle);
        float angle = getAngle() + 90;
        
        Bullet bullet = Bullet(getXPos(), getYPos(), angle, primaryWeaponType,getName());
        bullet.updateModelMatrix(getXPos(),getYPos(),angle);
        bullets.push_back(bullet);
        
        lastTimePrimary = currentTime;
    }
}

void Player::shootSecondary(float dirXPos, float dirYPos){
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTimeSecondary);
    
    if(deltaTime > fireRateSecondary){
        //calculate angle:
        //float xdif = getXPos() - (dirXPos*1000);
        //float ydif = getYPos() - (dirYPos*1000);
        
        //float angle = (atan2(ydif, xdif) * 180.0 / PI) + 90;
        //setAngle(angle);
        float angle = getAngle() + 90;
        
        Bullet bullet = Bullet(getXPos(), getYPos(), angle, secondaryWeaponType,getName());
        bullets.push_back(bullet);
        
        lastTimeSecondary = currentTime;
    }
}

void Player::updateAngleMousePos(float dirXPos, float dirYPos){
    float xdif = getXPos() - (dirXPos*1000);
    float ydif = getYPos() - (dirYPos*1000);
    
    float angle = (atan2(ydif, xdif) * 180.0 / PI) + 90;

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

float Player::getAngle() {
    return GameObject::getAngle();
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

void Player::updateModelMatrix(float _xpos, float _ypos, float _rot){
    Mesh meshTemp;
    // Translate player position
    glm::vec3 temp = glm::vec3(_xpos,_ypos, -200);
    meshTemp.translate(temp);
    
    // Apply standard rotation
    float std_rot = 90.f/180.f *PI;
    meshTemp.rotate(glm::vec3(0.f, 0.f, 1.f), std_rot);
    std_rot = 90.f / 180.f * PI;
    meshTemp.rotate(glm::vec3(1.f, 0.f, 0.f), std_rot);
    
    // Apply rotation caused by player
    _rot = _rot /180.f *PI;
    meshTemp.rotate(glm::vec3(0.f, 1.f, 0.f), _rot);
    mesh = meshTemp;
    
}