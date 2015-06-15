//
//  Player.h
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__Player__
#define __BaseDefender__Player__

#include "GameObject.h"
#include "Mesh.h"

class Enemie;

class Player:GameObject{
public:
    Player(std::string _name,
           int _hp,
           float _xPos,
           float _yPos,
           float _width,
           float _height,
           float _angle,
           int _level);
    Mesh getMesh();
    void setMesh(Mesh _mesh);
    
    void updatePlayer();
    void shootPrimary(float dirXPos, float dirYPos);
    void shootSecondary(float dirXPos, float dirYPos);
    void updateAngleMousePos(float dirXPos, float dirYPos);
    std::vector<Bullet>* getBullets();
    float getFireRatePrimary();
    
    //getter & setters
    float getXPos();
    float getYPos();
    int getHp();
    void setNewPos(float newXPos, float newYPos);
    float getAngle();
    
    //remove bullet
    void updateBullets();
    void removeBullet(int index);
    
    //enemie hit
    bool getHitByEnemie(float enemieXPos, float enemieYPos, float enemieWidth, int dmg);
    
    //update model Matrix
    void updateModelMatrix(float _xpos, float _ypos, float _rot);
private:
    std::vector<Bullet> bullets;
    float fireRatePrimary;
    float fireRateSecondary;
    
    
    //movement
    float nextXpos;
    float nextYpos;
    float agility;
    float movementSpeed;
    float movementXdir;
    float movementYdir;
    
    
    //weapontype
    WeaponType primaryWeaponType;
    WeaponType secondaryWeaponType;
    
    //time
    double lastTimePrimary;
    double lastTimeSecondary;
    
    Mesh mesh;
};

#endif /* defined(__BaseDefender__Player__) */
