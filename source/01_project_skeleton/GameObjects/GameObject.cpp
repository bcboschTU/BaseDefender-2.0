//
//  GameObject.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "GameObject.h"


GameObject::GameObject(std::string _name,
                       int _hp,
                       float _xPos,
                       float _yPos,
                       float _width,
                       float _height,
                       float _angle,
                       int _level){
    name = _name;
    hp = _hp;
    xPos = _xPos;
    yPos = _yPos;
    width = _width;
    height = _height;
    angle = _angle;
    level = _level;
}

Mesh GameObject::draw(){
    std::cout << "draw, not overwritten\n";
}


std::string GameObject::getName(){
    return name;
}
void GameObject::setName(std::string _name){
    name = _name;
}
int GameObject::getHp(){
    return hp;
}
void GameObject::setHp(int _hp){
    hp = _hp;
}
float GameObject::getXPos(){
    return xPos;
}
void GameObject::setXPos(float _xPos){
    xPos = _xPos;
}
float GameObject::getYPos(){
    return yPos;
}
void GameObject::setYPos(float _yPos){
    yPos = _yPos;
}
float GameObject::getWidth(){
    return width;
}
void GameObject::setWidth(float _width){
    width = _width;
}
float GameObject::getHeight(){
    return height;
}
void GameObject::setHeight(float _height){
    height = _height;
}
float GameObject::getAngle(){
    return angle;
}
void GameObject::setAngle(float _angle){
    angle = _angle;
}
int GameObject::getLevel(){
    return level;
}
void GameObject::setLevel(int _level){
    level = _level;
}

float GameObject::calculateDistance(float x1, float x2, float y1, float y2){
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
}