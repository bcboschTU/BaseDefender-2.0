//
//  Level.h
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__Level__
#define __BaseDefender__Level__

#include <stdio.h>
#include <vector>
#include "LightingTechnique.h"
#include "Renderer.h"
#include <GLUT/glut.h>
#include <pthread.h>

#include "Bullet.h"
#include "Player.h"
#include "Base.h"
#include "Turret.h"
#include "Enemie.h"
#include "Background.h"
#include "Explosion.h"
#include "texture.hpp"
#include "Mesh.h"
#include "Camera.hpp"

class Level{
public:
    Level();
    Level(int type, int width, int height);
    void loadLevel();
    void drawLevel(Camera *camera, LightingTechnique *lightingEffect);
    void drawMesh(Mesh mesh, Camera *camera, LightingTechnique *lightingEffect, glm::mat4 _Model);
    void drawHud();
    void updateLevel();
    void getBullets();
    void checkIfBulletsHit();
    void checkIfBulletsHitEnemy(int begin, int end);
    void checkIfEnemieHit();
    void checkRoundUpdate();
    void checkMultiplerScore();
    void updateEnemieVector();
    void generateEnemies();
    Player* getPlayer(int i);
    float rand_FloatRange(float a, float b, bool between);
    void pauseGame();
    void checkIfGameOver();
    void resetLevel();
    void loadTextures();
    void loadModels();
    void updatePointNormal(float *normal, int vertex, int shape);
    void CrossProduct(float *a, float *b, float *normal);
    void renderString(float x, float y, void *font, const std::string &string);
    void generateExplosionBullet(float _xPos, float _yPos, WeaponType _weaponType);
    void generateExplosion(float _xPos, float _yPos, ExplosionType _explosionType);
    void updateExplosions();
    
    void setWidth(int _width);
    void setHeight(int _height);
    
    void roundStart(int round);
    void cleanUp();
private:
    int type;

    std::vector<Player> players;
    std::vector<Bullet*> bullets;
    std::vector<Base> bases;
    std::vector<Turret> turrets;
    std::vector<Enemie> enemies;
    std::vector<Explosion> explosions;
    Background background = Background(0,0,20,20);
    
    std::vector<GLuint> textures;
    std::vector<std::string> textureNamesPosition;
    
    bool pause;
    float lastTimePause;
    float lastTimeLevel;
    
    int score;
    int multiplier;
    int multiplierBaseScore;
    int round;
    bool roundStartStop;
    bool roundStartShowText;
    float roundStartShowTextTimer;
    float roundStartShowTextTime;
    int enemyAmount;
    float enemySpawnRate;
    float enemySpawnLoop;
    
    int width;
    int height;

    std::vector<float> normals;
    
    Mesh explosionMesh;
    Mesh bulletMesh;
    Mesh turretMesh;
    Mesh playerMesh;
    Mesh baseMesh;
    Mesh enemyMesh;
    
    glm::mat4 Projection;
    glm::mat4 View;
    glm::mat4 Model;
    glm::mat4 MVP;
    glm::mat3 ModelView3x3Matrix;
    
    GLuint VertexArrayID;
    
};


#endif /* defined(__BaseDefender__Level__) */
