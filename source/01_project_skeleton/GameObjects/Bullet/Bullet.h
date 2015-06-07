//
//  Bullet.h
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__Bullet__
#define __BaseDefender__Bullet__
#define PI 3.1415926535897932384626433832795

#include <stdio.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include "Mesh.h"

enum WeaponType{
    NORMAL = 1,
    EXPLOSIVE = 2,
    DUAL = 3,
    ROCKET = 4,
    NUKE = 5
};

class Bullet{
public:
    Bullet(float _xPos, float _yPos, float _angle, WeaponType _bulletType, std::string _owner);
    Mesh getMesh();
    bool getDrawAble();
    
    void setMesh(Mesh _mesh);
    void bulletSetup();
    void updateBullet();
    
    void explodeBullet();
    bool getExploding();
    void setExploding(bool _exploding);
    void checkIfAlive();
    void setDestroyed(bool _destroyed);
    bool getDestroyed();
    float getXPos();
    float getYPos();
    float getWidth();
    int getDmg();
    WeaponType getType();
    
    //update model Matrix
    void updateModelMatrix(float _xpos, float _ypos, float _rot);
private:
    float xPos;
    float yPos;
    float angle;
    WeaponType bulletType;
    float width;
    float height;
    float speed;
    int dmg;
    
    //owners of the bullet
    std::string owner;
    //lifetime of bullet & destroy
    float lifeStart;
    float lifetime;
    bool destroyed;
    
    //explosive:
    bool exploding;
    double explodingTime;
    Mesh mesh;
};

#endif /* defined(__BaseDefender__Bullet__) */
