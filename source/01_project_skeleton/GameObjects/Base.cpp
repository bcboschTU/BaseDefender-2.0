//
//  Base.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Base.h"

Base::Base(std::string _name,
           int _hp,
           float _xPos,
           float _yPos,
           float _width,
           float _height,
           float _angle,
           int _level):GameObject(_name,_hp,_xPos,_yPos,_width,_height,_angle,_level){
    
    lightDirection = 0;
    
    Mesh meshTemp;
    glm::vec3 temp = glm::vec3(_xPos,_yPos, -200.f);
    meshTemp.translate(temp);

    meshTemp.scale(glm::vec3(14.0f, 14.0f, 14.0f));
    setMesh(meshTemp);
}

Mesh Base::getMesh(){
    return mesh;
}
void Base::setMesh(Mesh _mesh){
    mesh = _mesh;
}


bool Base::getHitByEnemie(float enemieXPos, float enemieYPos, float enemieWidth, int dmg){
    float distance = calculateDistance(getXPos(), enemieXPos, getYPos(), enemieYPos);
    float hitDistance = getWidth() + enemieWidth;
    if(distance < hitDistance){
        setHp(getHp()- dmg);
        return true;
    }
    return false;
}

float Base::getXPos(){
    return GameObject::getXPos();
}
float Base::getYPos(){
    return GameObject::getYPos();
}

int Base::getHp(){
    return GameObject::getHp();
}

void Base::updateBase() {
    lightDirection += 1.5f;
    
    while(lightDirection < 0)
        lightDirection += 360;
    
    while(lightDirection > 360)
        lightDirection -= 360;
}

float Base::getLightDirection() {
    return lightDirection;
}

void Base::updateModelMatrix(float _xpos, float _ypos, float _rot){
    Mesh meshTemp;
    
    mesh = meshTemp;
    
}