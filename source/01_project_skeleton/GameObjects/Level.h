//
//  Level.h
//  opengl-series
//
//  Created by Bert Bosch on 05-06-15.
//
//

#ifndef __opengl_series__Level__
#define __opengl_series__Level__




#include <stdio.h>
#include <vector>
#include "LightingTechnique.h"
#include "Renderer.h"
#include <GLUT/glut.h>
#include <pthread.h>

#include "Player.h"
#include "Base.h"
#include "Turret.h"
#include "Enemie.h"
#include "Explosion.h"
#include "texture.hpp"
#include "Mesh.h"
#include "Camera.hpp"



class Level{
public:
    //empty constructor for main
    Level();
    
    
    //setup
    Level(int type, int width, int height);
    Level(int type, int width, int height, const char* file);
    void loadLevelFromFile(const char* filename);
    
    
    //graphics
    void drawLevel();
    void drawHUD();
    void drawMesh(Mesh mesh, Camera* camera, LightingTechnique *lightingEffect, glm::mat4 _Model);
    void setupMeshes();
    void loadTextures();
    void initLightingEffect();
    void updateLighting();
    void cleanup();
    
    
    //game logic
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
    void generateExplosionBullet(float _xPos, float _yPos, WeaponType _weaponType);
    void generateExplosion(float _xPos, float _yPos, ExplosionType _explosionType);
    void updateExplosions();
    
    void setWidth(int _width);
    void setHeight(int _height);
    
    void roundStart(int round);
    
    
    
    
    //camera temp
    void updateCamera(float secondsElapsed,GLFWwindow* window);
    void OnScroll(GLFWwindow* window, double deltaX, double deltaY);
    Camera getCamera();
private:
    std::vector<Player> players;
    std::vector<Bullet*> bullets;
    std::vector<Base> bases;
    std::vector<Turret> turrets;
    std::vector<Enemie> enemies;
    std::vector<Explosion> explosions;
    //Background background = Background(0,0,20,20);
    
    
    int type;
    
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
    
    
    Mesh playerMesh;
    Mesh explosionMesh;
    Mesh bulletMesh;
    Mesh turretMesh;
    Mesh baseMesh;
    Mesh enemyMesh_100_50;
    Mesh enemyMesh_50_0;
    
    GLuint programID;
    GLuint MatrixID;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;
    
    GLuint DiffuseTexturePlayer;
    GLuint DiffuseTextureEnemie;
    GLuint DiffuseTextureTurret;
    
    
    
    //GLuint NormalTexture;
    //GLuint NormalTextureID;
    
    //buffers
    GLuint VertexArrayID;
    
    LightingTechnique* lightingEffect;
    DirectionalLight directionalLight;
    
    //temp
    Camera camera;
    double gScrollY = 0.0;
    GLfloat gDegreesRotated = 0.0f;
    
    glm::mat4 Projection;
    glm::mat4 View;
    glm::mat4 Model;
    glm::mat4 MVP;
    glm::mat3 ModelView3x3Matrix;
};


#endif /* defined(__opengl_series__Level__) */
