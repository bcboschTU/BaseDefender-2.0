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
            width = 0.05;
            height = 0.05;
            widthMax = 0.1;
            heightMax = 0.1;
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

void Explosion::updateExplosion(){
    if(width < widthMax){
        width  = width + 0.01;
    }
    if(height < heightMax){
        height = height + 0.01;
    }
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
