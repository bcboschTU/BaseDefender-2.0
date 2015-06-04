//
//  Background.h
//  BaseDefender
//
//  Created by Bert Bosch on 03-03-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__Background__
#define __BaseDefender__Background__

#include <stdio.h>
#include <GLFW/glfw3.h>

class Background{
public:
    Background(float _xPos, float _yPos, float _width, float _height);
    void drawBackGround();
    float getXPos();
    void setXPos(float _xPos);
    float getYPos();
    void setYPos(float _yPos);
    float getWidth();
    void setWidth(float _width);
    float getHeight();
    void setHeight(float _height);
private:
    float xPos;
    float yPos;
    float width;
    float height;
    
};

#endif /* defined(__BaseDefender__Background__) */
