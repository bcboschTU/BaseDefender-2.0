//
//  Turret.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Turret.h"

Turret::Turret(std::string _name,
               int _hp,
               float _xPos,
               float _yPos,
               float _width,
               float _height,
               float _angle,
               int _level,
               float _rangeBegin,
               float _rangeEnd,
               WeaponType _weaponType):GameObject(_name,_hp,_xPos,_yPos,_width,_height,_angle,_level){
    rangeBegin = _rangeBegin;
    rangeEnd = _rangeEnd;
    weaponType = _weaponType;
    fireRate = 0.1;
    range = 5;
    lastTime = glfwGetTime();
}

void Turret::draw(){
    glColor3f(0.0f, 1.0f, 0.0f);
    
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    glPushMatrix();
    glTranslatef(getXPos(), getYPos(), 0);
    glScaled(3, 3, 1);
    glRotated(getAngle(), 0.0, 0.0, 1.0);
    glTranslatef(-getXPos(), -getYPos(), 0);
    
    
    
    /*
    glBegin(GL_POLYGON);
    for(double i = 0; i < 2 * PI; i += PI / 32){ //<-- Change this Value
        glVertex3f(cos(i) * getWidth(), sin(i) * getHeight(), 0.0);
    }
    glEnd();
    */
    
    glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
        glColor4f(1.0f, 1.0f, 1.0f,1.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(getXPos() - getWidth(), getYPos() - getHeight());    // x, y
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(getXPos() + getWidth(), getYPos() - getHeight());
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(getXPos() + getWidth(), getYPos() + getHeight());
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(getXPos() - getWidth(), getYPos() + getHeight());
    glEnd();
    
    glPopMatrix();
}

void Turret::updateTurret(){

}

void Turret::levelUpWeapon(){
    int weaponTypeNext = (int)weaponType;
    weaponType = WeaponType(weaponTypeNext +1);
}
void Turret::levelUpRange(){
    
}
void Turret::levelUpFireRate(){
    
}
void Turret::levelUp(){
    
}


void Turret::shoot(float dirXPos, float dirYPos){
    float currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    
    if(deltaTime > fireRate){
        //calculate angle:
        float xdif = getXPos() - dirXPos;
        float ydif = getYPos() - dirYPos;
        
        float angle = (atan2(ydif, xdif) * 180.0 / PI) + 180;
        setAngle(angle);
        
        Bullet bullet = Bullet(getXPos(), getYPos(), angle, weaponType,getName());
        bullets.push_back(bullet);
        
        lastTime = currentTime;
    }
}

std::vector<Bullet>* Turret::getBullets(){
    updateBullets();
    
    return &bullets;
}

void Turret::setTarget(std::vector<Enemie> *enemies){
    int closest = -1;
    int distanceClosest  = 10* range;
    for (int i = 0; i<enemies->size(); i++) {
        Enemie *enemie = &enemies->at(i);
        float xPosEnemie = enemie->getXPos();
        float yPosEnemie = enemie->getYPos();
        float distance = calculateDistance(getXPos(),xPosEnemie,getYPos(),yPosEnemie);
        float xdif = getXPos() - xPosEnemie;
        float ydif = getYPos() - yPosEnemie;
        
        float angle = (atan2(ydif, xdif) * 180.0 / PI) + 180;
        if(angle > rangeBegin && angle < rangeEnd){
            if(distance < range && distanceClosest > distance){
                closest = i;
                distanceClosest = distance;
            }
        }
    }
    
    if (closest != -1) {
        Enemie *enemie = &enemies->at(closest);
        shoot(enemie->getXPos(), enemie->getYPos());
    }
    
}

void Turret::updateBullets(){
    for(int i = 0; i< bullets.size(); i++){
        Bullet *bullet = &bullets[i];
        bullet->updateBullet();
        if(bullet->getDestroyed()){
            removeBullet(i);
        }
        
    }
}

void Turret::removeBullet(int index){
    bullets.erase(bullets.begin() + index);
}

float Turret::calculateDistance(float x1, float x2, float y1, float y2){
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
}