//
//  Base.h
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__Base__
#define __BaseDefender__Base__

#include "GameObject.h"


class Base:GameObject{
public:
    Base(std::string _name,
         int _hp,
         float _xPos,
         float _yPos,
         float _width,
         float _height,
         float _angle,
         int _level);
    
    Mesh getMesh();
    void setMesh(Mesh _mesh);
    
    float getXPos();
    float getYPos();
    int getHp();
    bool getHitByEnemie(float enemieXPos, float enemieYPos, float enemieWidth, int dmg);
private:
    Mesh mesh;
    
};

#endif /* defined(__BaseDefender__Base__) */
