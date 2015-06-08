//
//  Explosion.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 02-03-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Explosion.h"



Explosion::Explosion(float _xPos, float _yPos, ExplosionType _type){
    xPos = _xPos;
    yPos = _yPos;
    type = _type;
    lifeStart = glfwGetTime();
    width = 0;
    height = 0;
    destroyed = false;
    explosionSetup();
}

void Explosion::explosionSetup(){
    switch (type) {
        case SMALL:
            width = 0.1;
            height = 0.1;
            widthMax = 0.2;
            heightMax = 0.2;
            offSetMin = -0.1;
            offSetPlus = 0.1;
            amountOfExplosions = 1;
            lifetime = 0.35;
            break;
        case MEDIUM:
            width = 0.05;
            height = 0.05;
            widthMax = 0.2;
            heightMax = 0.2;
            offSetMin = -0.1;
            offSetPlus = 0.1;
            amountOfExplosions = 5;
            lifetime = 0.4;
            break;
        case GRAND:
            width = 0.5;
            height = 0.5;
            widthMax = 4;
            heightMax = 4;
            offSetMin = -0.2;
            offSetPlus = 0.2;
            amountOfExplosions = 20;
            lifetime = 0.6;
            break;
        default:
            break;
    }
    
    for (int i = 0; i<amountOfExplosions; i++) {
        offSetsX.push_back(generateRandomOffset(offSetMin, offSetPlus));
        offSetsY.push_back(generateRandomOffset(offSetMin, offSetPlus));
    }
}

Mesh Explosion::getMesh(){
    return mesh;
}
void Explosion::setMesh(Mesh _mesh){
    mesh = _mesh;
}

bool Explosion::getDrawAble(){
    checkIfAlive();
    if(!destroyed){
        return true;
    }
    else{
        return false;
    }
    
}

void Explosion::updateExplosion(){
    if(width < widthMax){
        width  = width + 0.5;
    }
    if(height < heightMax){
        height = height + 0.5;
    }
    updateModelMatrix(xPos, yPos, 0);
}

void Explosion::checkIfAlive(){
    float currentTime = glfwGetTime();
    if(currentTime - lifeStart > lifetime){
        destroyed = true;
    }
}

bool Explosion::getDestroyed(){
    return destroyed;
}

float Explosion::generateRandomOffset(float a, float b){
    return((b-a)*((float)rand()/RAND_MAX))+a;
}

void Explosion::updateModelMatrix(float _xpos, float _ypos, float _rot){
    Mesh meshTemp;
    glm::vec3 temp = glm::vec3(_xpos,_ypos, -200);
    meshTemp.translate(temp);
    
    meshTemp.scale(glm::vec3(width, width, width));
    
    _rot = _rot /180 *PI;
    meshTemp.rotate(glm::vec3(0.f, 0.f, 1.f), _rot);
    mesh = meshTemp;
    
}
