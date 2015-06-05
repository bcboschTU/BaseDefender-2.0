//
//  GameObject.h
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__GameObject__
#define __BaseDefender__GameObject__
#define PI 3.1415926535897932384626433832795

#include <stdio.h>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include "Mesh.h"

#include "Bullet.h"


class GameObject{
public:
    GameObject(std::string _name,
               int hp,
               float _xPos,
               float _yPos,
               float _width,
               float _height,
               float _angle,
               int _level);    
    
    //getters and setters
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
};

#endif /* defined(__BaseDefender__GameObject__) */
