//
//  Background.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 03-03-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Background.h"

Background::Background(float _xPos, float _yPos, float _width, float _height){
    xPos = _xPos;
    yPos = _yPos;
    width = _width;
    height = _height;
}

void Background::drawBackGround(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    
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


void Background::setXPos(float _xPos){
    xPos = _xPos;
}

float Background::getXPos(){
    return xPos;
}

void Background::setYPos(float _yPos){
    yPos = _yPos;
}


float Background::getYPos(){
    return yPos;
}


void Background::setWidth(float _width){
    width = _width;
}


float Background::getWidth(){
    return width;
}

void Background::setHeight(float _height){
    height = _height;
}

float Background::getHeight(){
    return height;
}