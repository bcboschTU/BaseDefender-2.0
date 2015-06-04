//
//  Explosion.h
//  BaseDefender
//
//  Created by Bert Bosch on 02-03-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__Explosion__
#define __BaseDefender__Explosion__
#define PI 3.1415926535897932384626433832795

#include <stdio.h>
#include "Mesh.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <vector>

enum ExplosionType{
    SMALL = 0,
    MEDIUM = 1,
    GRAND = 2
};

class Explosion{
public:
    Explosion(float _xPos, float _yPos, ExplosionType type);
    void explosionSetup();
    Mesh draw();
    void updateExplosion();
    void checkIfAlive();
    bool getDestroyed();
    float generateRandomOffset(float x, float y);
private:
    float xPos;
    float yPos;
    ExplosionType type;
    float width;
    float widthMax;
    float height;
    float heightMax;
    
    std::vector<float> offSetsX;
    std::vector<float> offSetsY;
    float offSetMin;
    float offSetPlus;
    //std::vector<float> maxSize;
    float amountOfExplosions;
    
    float lifeStart;
    float lifetime;
    bool destroyed;
    
    Mesh mesh;
    
};

#endif /* defined(__BaseDefender__Explosion__) */
