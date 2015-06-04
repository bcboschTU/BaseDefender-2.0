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
}


Mesh Base::draw(){
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glPushMatrix();
//    
//    glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
//        glColor4f(1.0f, 1.0f, 1.0f,1.0f);
//        glTexCoord2f(0.0f, 1.0f);
//        glVertex2f(getXPos() - getWidth(), getYPos() - getHeight());    // x, y
//        glTexCoord2f(0.0f, 0.0f);
//        glVertex2f(getXPos() + getWidth(), getYPos() - getHeight());
//        glTexCoord2f(1.0f, 0.0f);
//        glVertex2f(getXPos() + getWidth(), getYPos() + getHeight());
//        glTexCoord2f(1.0f, 1.0f);
//        glVertex2f(getXPos() - getWidth(), getYPos() + getHeight());
//    glEnd();
//    
//    glPopMatrix();
    
    return mesh;
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