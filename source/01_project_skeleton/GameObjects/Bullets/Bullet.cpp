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
    lifetime = 4.0;
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
            speed = 0.2;
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

void Bullet::draw(){
    if(!destroyed){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glTranslatef(xPos, yPos, 0);
        
        /*
        glBegin(GL_TRIANGLE_FAN);
        {
            glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
            glVertex3f(0, 0, 0);
            // Set edge colour for rest of shape
            glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
            for (float angle=0; angle<= PI*2; angle+=((PI*2)/32) )
            {
                glVertex3f( width*(float)cos(angle),
                              width*(float)sin(angle), 0.0f);
            }
            glVertex3f(0+ width, 0, 0.0f);
        }
        glEnd();
        */
        
        
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        glVertex3f(0, 0, 0);
        // Set edge colour for rest of shape
        glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
        for(double i = 0; i < 2 * PI; i += PI / 16){ //<-- Change this Value
            glVertex3f(cos(i) * width, sin(i) * height, 0.0);
        }
        glVertex3f(width, 0, 0.0f);
        glEnd();
        
        
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
        glVertex3f(0, 0, 0);
        // Set edge colour for rest of shape
        glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
        for(double i = 0; i < 2 * PI; i += PI / 16){ //<-- Change this Value
            glVertex3f(cos(i) * (width/4)*3, sin(i) * (height/4)*3, 0.0);
        }
        glVertex3f((width/4)*3, 0, 0.0f);
        glEnd();
        
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
        glVertex3f(0, 0, 0);
        // Set edge colour for rest of shape
        glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
        for(double i = 0; i < 2 * PI; i += PI / 8){ //<-- Change this Value
            glVertex3f(cos(i) * (width/8)*3, sin(i) * (height/8)*3, 0.0);
        }
        glVertex3f((width/8)*3, 0, 0.0f);
        glEnd();
        
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glVertex3f(0, 0, 0);
        // Set edge colour for rest of shape
        glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
        for(double i = 0; i < 2 * PI; i += PI / 8){ //<-- Change this Value
            glVertex3f(cos(i) * (width/12)*3, sin(i) * (height/12)*3, 0.0);
        }
        glVertex3f((width/12)*3, 0, 0.0f);
        glEnd();
        
        glPopMatrix();
        
    }
    
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