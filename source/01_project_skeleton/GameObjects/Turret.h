//
//  Turret.h
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__Turret__
#define __BaseDefender__Turret__

#include "GameObject.h"
#include "Enemie.h"

class Turret:GameObject{
public:
    Turret(std::string _name,
           int _hp,
           float _xPos,
           float _yPos,
           float _width,
           float _height,
           float _angle,
           int _level,
           float _rangeBegin,
           float _rangeEnd,
           WeaponType _weaponType);
    Mesh getMesh();
    void setMesh(Mesh _mesh);
    void updateTurret();
    void shoot(float dirXPos, float dirYPos);
    void levelUpWeapon();
    void levelUpRange();
    void levelUpFireRate();
    void levelUp();
    std::vector<Bullet>* getBullets();
    void setTarget(std::vector<Enemie> *enemies);
    float calculateDistance(float x1, float x2, float y1, float y2);
    //remove bullet
    void updateBullets();
    void removeBullet(int index);
    
    //getter & setters
    float getXPos();
    float getYPos();
    float getAngle();
    int getHp();
    void setNewPos(float newXPos, float newYPos);
    
    //update model Matrix
    void updateModelMatrix(float _xpos, float _ypos, float _rot);
private:
    std::vector<Bullet> bullets;
    WeaponType weaponType;
    float fireRate;
    float range;
    float rangeBegin;
    float rangeEnd;
    float lastTime;
    Mesh mesh;
};


#endif /* defined(__BaseDefender__Turret__) */
