//
//  Bullet.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Bullet.h"


Bullet::Bullet(float _xPos, float _yPos, float _angle, WeaponType _bulletType, std::string _owner){
    xPos = _xPos;
    yPos = _yPos;
    angle = _angle;
    bulletType = _bulletType;
    owner = _owner;
    lifeStart = glfwGetTime();
    lifetime = 2.0;
    destroyed = false;
    exploding = false;
    explodingTime = 0.6;
    bulletSetup();
    
}

void Bullet::bulletSetup(){
    switch (bulletType) {
        case NORMAL:
            width = 0.1;
            height = 0.1;
            speed = 8;
            dmg = 10;
            break;
        case EXPLOSIVE:
            width = 0.15;
            height = 0.15;
            speed = 0.08;
            dmg = 10;
            break;
        case DUAL:
            width = 0.05;
            height = 0.05;
            speed = 0.01;
            dmg = 10;
            break;
        case ROCKET:
            width = 0.1;
            height = 0.1;
            speed = 0.1;
            dmg = 10;
            break;
        case NUKE:
            width = 0.1;
            height = 0.1;
            speed = 0.008;
            dmg = 60;
            lifetime = lifetime*5;
            explodingTime = explodingTime*2;
            break;
        default:
            break;
    }
}


Mesh Bullet::getMesh(){
    return mesh;
}

bool Bullet::getDrawAble(){
    if(!destroyed){
        return true;
    }
    else{
        return false;
    }
    
}
void Bullet::setMesh(Mesh _mesh){
    mesh = _mesh;
}

void Bullet::updateBullet(){
    //life
    checkIfAlive();
    
    
    if(exploding && bulletType == EXPLOSIVE){
        width += 0.03;
        height += 0.03;
    }
    else if(exploding && bulletType == NUKE){
        width += 0.06;
        height += 0.06;
    }
    else{
        //update xpos and ypos;
        float xPosNew = xPos;
        float yPosNew = yPos;
        
        float xdif = cosf(angle * PI/180);
        float ydif = sinf(angle * PI/180);
        
        
        xPos = xPosNew + xdif*speed;
        yPos = yPosNew + ydif*speed;
        updateModelMatrix(xPos, yPos, 0);
    }
}

void Bullet::explodeBullet(){
    if (exploding == false) {
        exploding = true;
        lifeStart = glfwGetTime();
        lifetime = explodingTime;
    }
    
}

bool Bullet::getExploding(){
    return exploding;
}

void Bullet::setExploding(bool _exploding){
    exploding = _exploding;
}

void Bullet::checkIfAlive(){
    float currentTime = glfwGetTime();
    if(currentTime - lifeStart > lifetime){
        destroyed = true;
    }
}

bool Bullet::getDestroyed(){
    if(destroyed){
        return true;
    }
    
    float currentTime = glfwGetTime();
    if(currentTime - lifeStart > lifetime){
        return true;
    }
    return false;
}

float Bullet::getXPos(){
    return xPos;
}
float Bullet::getYPos(){
    return yPos;
}

float Bullet::getWidth(){
    return width;
}

int Bullet::getDmg(){
    return dmg;
}

WeaponType Bullet::getType(){
    return bulletType;
}

void Bullet::setDestroyed(bool _destroyed){
    if(bulletType == EXPLOSIVE || bulletType == NUKE){
        explodeBullet();
    }
    else{
        destroyed = _destroyed;
    }
}

void Bullet::updateModelMatrix(float _xpos, float _ypos, float _rot){
    Mesh meshTemp;
    glm::vec3 temp = glm::vec3(_xpos,_ypos, -200);
    meshTemp.translate(temp);
    _rot = _rot /180 *PI;
    meshTemp.rotate(glm::vec3(0.f, 0.f, 1.f), _rot);
    mesh = meshTemp;
    
}