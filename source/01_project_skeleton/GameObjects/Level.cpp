//
//  Level.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Level.h"
//QuadtreeBullet quadtree = QuadtreeBullet( -10.0f, -10.0f, 20.0f, 20.0f, 0, 10, 3 );
Level::Level(){
    
}


Level::Level(int _type, int _width, int _height){
    type = _type;
    loadLevel();
    pause = false;
    lastTimeLevel = glfwGetTime();
    lastTimePause = glfwGetTime();
    background.setXPos(0);
    background.setYPos(0);
    background.setWidth(10);
    background.setHeight(6.5);
    width = _width;
    height =_height;
}

void Level::loadLevel(){
    score = 0;
    multiplierBaseScore = 0;
    multiplier = 1;
    round = 1;
    roundStart(1);
    roundStartShowText = true;
    roundStartShowTextTimer = glfwGetTime();
    roundStartShowTextTime = 2.0;
    
    Player player1 = Player("Player1", 200, 3, 1, 0.4, 0.4, 0, 1);
    players.push_back(player1);
    
    Base base1 = Base("Base1", 500, 0, 0, 0.8, 0.8, 0, 1);
    bases.push_back(base1);
    
    Turret turret11 = Turret("Turret1Base1", 100, 0.7, 0.7, 0.15, 0.15, 45, 1, 10, 80, NORMAL);
    turret11.levelUpWeapon();
    turrets.push_back(turret11);
    
    Turret turret12 = Turret("Turret2Base1", 100, -0.7, -0.7, 0.15, 0.15, 225, 1, 190, 260, NORMAL);
    turrets.push_back(turret12);
    
    
    Turret turret13 = Turret("Turret3Base1", 100, -0.7, 0.7, 0.15, 0.15, 135, 1, 100, 170, NORMAL);
    turrets.push_back(turret13);
    
    Turret turret14 = Turret("Turret4Base1", 100, 0.7, -0.7, 0.15, 0.15, 315, 1, 280, 350, NORMAL);
    turrets.push_back(turret14);
    
    
     
    loadTextures();
    
    loadModels();
}

void Level::drawLevel(){
    if(!pause){
        //update all the vector array elements first
        updateLevel();
    }
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture3);
    background.drawBackGround();
    
    
    
    glBindTexture(GL_TEXTURE_2D, texture2);
    for (int i = 0; i<turrets.size(); i++) {
        Turret * turret = &turrets[i];
        turret->draw();
    }
    
    glBindTexture(GL_TEXTURE_2D, texture1);
    for (int i = 0; i<bases.size(); i++) {
        Base * base = &bases[i];
        base->draw();
        //base->drawObj(shapes, materials);
    }
    
    //draw all the elements of all the vector arrays
    glBindTexture(GL_TEXTURE_2D, texture4);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        player->draw();
        //player->drawObj(shapes, materials,normals);
    }
    
    glBindTexture(GL_TEXTURE_2D, texture4);
    for (int i = 0; i<enemies.size(); i++) {
        Enemie * enemie = &enemies[i];
        enemie->draw();
        //enemie->drawObj(shapes, materials,normals);
    }
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    
    for (int i = 0; i<bullets.size(); i++) {
        Bullet *bullet = bullets[i];
        bullet->draw();
    }
    
    for (int i = 0; i<explosions.size(); i++) {
        Explosion *explosion = &explosions[i];
        explosion->draw();
    }
    
}

void Level::drawHud(){
    
//    std::string baseString = "base1 Health: " + std::to_string(bases[0].getHp());
//    
//    renderString(5, 20, GLUT_BITMAP_HELVETICA_18, baseString);
//    
//    
//    std::string healthString = "player1 Healt: " + std::to_string(players[0].getHp());
//    
//    renderString(5, 40, GLUT_BITMAP_HELVETICA_18, healthString);
//    
//    
//    std::string scoreString = "score: " + std::to_string(score);
//    
//    renderString(5, 60, GLUT_BITMAP_HELVETICA_18, scoreString);
//    
//    
//    std::string multiplierString = "multiplier: " + std::to_string(multiplier);
//    
//    renderString(5, 80, GLUT_BITMAP_HELVETICA_18, multiplierString);
//    
//    std::string roundString = "Round: " + std::to_string(round);
//    
//    renderString(5, 100, GLUT_BITMAP_HELVETICA_18, roundString);
//    
//    if(roundStartShowText){
//        std::string roundString = "ROUND START: " + std::to_string(round);
//        
//        renderString(width/2 - 80, height/4, GLUT_BITMAP_HELVETICA_18, roundString);
//    }
    /*
     glColor3f(0.0f, 255.0f, 1.0f);
     glBegin(GL_QUADS);
     glVertex2f(0.0, 0.0);
     glVertex2f(40.0, 0.0);
     glVertex2f(40.0, 40.0);
     glVertex2f(0.0, 10.0);
     glEnd();
     */
}


void Level::updateLevel(){
    checkIfGameOver();
    //clear all the bullets from last frame
    checkRoundUpdate();
    checkMultiplerScore();
    
    bullets.clear();
    //quadtree.empty();
    //get all bullets:
    getBullets();
    
    
    //check if a bullet hits anything
    checkIfBulletsHit();
    //check if a enemy hits a player or a turret
    checkIfEnemieHit();
    
    generateEnemies();
    
    updateExplosions();
    
    //update player
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        player->updatePlayer();
    }
    
    //update enemie
    updateEnemieVector();
    for (int i = 0; i<enemies.size(); i++) {
        Enemie * enemie = &enemies[i];
        enemie->updateEnemie();
    }
    
    //update the turrets targets
    for (int i = 0; i< turrets.size(); i++){
        Turret *turret = &turrets[i];
        turret->setTarget(&enemies);
    }
    
    for(int i = 0; i<explosions.size(); i++){
        Explosion * explosion = &explosions[i];
        explosion->updateExplosion();
    }
}

void Level::getBullets(){
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        std::vector<Bullet> *tempBullets = player->getBullets();
        for(int j = 0; j<tempBullets->size(); j++){
            bullets.push_back(&tempBullets->at(j));
            //quadtree.AddObject(&tempBullets->at(j));
        }
    }
    
    for (int i = 0; i<turrets.size(); i++) {
        Turret * turret = &turrets[i];
        std::vector<Bullet> *tempBullets = turret->getBullets();
        for(int j = 0; j<tempBullets->size(); j++){
            bullets.push_back(&tempBullets->at(j));
            //quadtree.AddObject(&tempBullets->at(j));
        }
    }
    
}

void Level::checkIfBulletsHit(){
    for (int i = 0; i<players.size(); i++) {
        //Player * player = &players[i];
        //check if player is hit by a bullet
    }
    
    
    
    //TODO: multithreading:?
    for (int i = 0; i<enemies.size(); i++) {
        Enemie * enemie = &enemies[i];
        int bulletHit = enemie->gotHit(bullets);
        //int bulletHit = enemie->gotHitTree(&quadtree);
        if(bulletHit != -1){
            Bullet *bullet = bullets[bulletHit];
            generateExplosionBullet(bullet->getXPos(), bullet->getYPos(),bullet->getType());
        }
        //check if enemie is hit by a bullet
    }
    
    //update the turrets targets
    for (int i = 0; i< turrets.size(); i++){
        //Turret *turret = &turrets[i];
        //check if turret is hit by a bullet
    }
    
    
}

void Level::checkIfBulletsHitEnemy(int begin, int end){
    
}


void Level::checkIfEnemieHit(){
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        //check if player is hit by a enemie
        for (int i = 0; i<enemies.size(); i++) {
            Enemie * enemie = &enemies[i];
            bool hit = player->getHitByEnemie(enemie->getXPos(), enemie->getYPos(), enemie->getWidth(), enemie->getDmg());
            if(hit){
                multiplier = 1;
                multiplierBaseScore = score;
                enemie->setHp(enemie->getHp()-enemie->getDmg());
            }
        }
    }
    
    for (int i = 0; i< turrets.size(); i++){
        //Turret *turret = &turrets[i];
        //check if turret is hit by a enemie
    }
    
    for (int i = 0; i< bases.size(); i++){
        Base * base = &bases[i];
        //check if base is hit by a enemie
        for (int i = 0; i<enemies.size(); i++) {
            Enemie * enemie = &enemies[i];
            bool hit = base->getHitByEnemie(enemie->getXPos(), enemie->getYPos(), enemie->getWidth(), enemie->getDmg());
            if(hit){
                enemie->setHp(enemie->getHp()-enemie->getDmg());
            }
        }
    }
}

void Level::checkRoundUpdate(){
    if(roundStartShowText){
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - roundStartShowTextTimer);
        if(deltaTime > roundStartShowTextTime){
            roundStartShowText = false;
        }
    }
    
    if(enemies.size() <=0 && enemyAmount <= 0) {
        roundStartStop = !roundStartStop;
        roundStartShowText = true;
        roundStartShowTextTimer = glfwGetTime();
        round++;
        roundStart(round);
    }
}

void Level::checkMultiplerScore(){
    if(score - multiplierBaseScore > (100 * multiplier)){
        multiplierBaseScore = score;
        multiplier++;
    }
}


void Level::updateEnemieVector(){
    //check if enemie is alive, if not erase
    for (int i = 0; i<enemies.size(); i++) {
        Enemie* enemie = &enemies[i];
        if(enemie->getHp() <= 0){
            //add explosion:
            generateExplosion(enemie->getXPos(), enemie->getYPos(), MEDIUM);
            //remove enemie from enemies;
            enemies.erase(enemies.begin() + i);
            score += 1 * multiplier;
            
        }
    }
}

Player* Level::getPlayer(int i){
    return &players[i];
}


float Level::rand_FloatRange(float a, float b, bool between){
    float randomValue = ((b-a)*((float)rand()/RAND_MAX))+a;
    if (between) {
        if(randomValue > 10 || randomValue < -10){
            return randomValue;
        }
        else{
            return rand_FloatRange(a,b, between);
        }
    }
    else{
        return randomValue;
    }
}

void Level::generateEnemies(){
    if(!roundStartShowText){
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTimeLevel);
        if(deltaTime > enemySpawnRate && enemyAmount > 0){
            for(int i = 0; i< enemySpawnLoop; i++){
                float xPos = rand_FloatRange(-14,14, true);
                float yPos = rand_FloatRange(-14,14, false);
                Enemie enemie = Enemie("enemie", 50, xPos, yPos, 0.2, 0.2, 0, 1);
                enemie.setTargetPlayer(&players[0]);
                //enemie.setTargetBase(&bases[0]);
                enemies.push_back(enemie);
                lastTimeLevel = currentTime;
                enemyAmount--;
            }
        }
    }
}


void Level::pauseGame(){
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTimePause);
    if(deltaTime > 0.2){
        pause = !pause;
        lastTimePause = currentTime;
    }
    
    if(!pause){
        //unpause all vectors, set time.
    }
}

void Level::checkIfGameOver(){
    for (int i = 0; i<bases.size(); i++) {
        Player * player = &players[i];
        if(player->getHp() <= 0){
            resetLevel();
        }
    }
    
    for (int i = 0; i<players.size(); i++) {
        Base * base = &bases[i];
        if(base->getHp() <= 0){
            resetLevel();
        }
    }
}

void Level::resetLevel(){
    players.clear();
    bullets.clear();
    bases.clear();
    turrets.clear();
    enemies.clear();
    explosions.clear();
    glDeleteTextures(1, &texture1);
    glDeleteTextures(1, &texture2);
    glDeleteTextures(1, &texture3);
    glDeleteTextures(1, &texture4);
    glDeleteTextures(1, &texture5);
    loadLevel();
}

void Level::loadTextures(){
//    texture1 = loadPng("base.png");
//    texture2 = loadPng("tank_turret.png");
//    texture3 = loadPng("background4.png");
//    //texture4 = loadPng("Su-34_Fullback_P01.png");
//    texture4 = loadPng("B-2_Spirit_P01.png");
//    texture5 = loadPng("tank1.png");
}

void Level::renderString(float x, float y, void *font, const std::string &string)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    for (int n=0; n<string.size(); ++n) {
//        glutBitmapCharacter(font, string[n]);
    }
}

void Level::generateExplosionBullet(float _xPos, float _yPos, WeaponType _weaponType){
    if (_weaponType == NORMAL) {
        generateExplosion(_xPos,_yPos,SMALL);
    }
}

void Level::generateExplosion(float _xPos, float _yPos, ExplosionType _type){
    Explosion explosion = Explosion(_xPos,_yPos,_type);
    explosions.push_back(explosion);
}

void Level::updateExplosions(){
    for (int i = 0; i<explosions.size(); i++) {
        Explosion* explosion = &explosions[i];
        if(explosion->getDestroyed()){
            explosions.erase(explosions.begin() + i);
            
        }
    }
}

void Level::setWidth(int _width){
    width = _width;
}
void Level::setHeight(int _height){
    height = _height;
}

void Level::roundStart(int _round){
    int amountOfEnemy = 2;
    enemyAmount = amountOfEnemy * _round;
    int rate = (int)sqrt(_round);
    enemySpawnRate = 0.4 - (round/100)*2;
    enemySpawnLoop = 2 * rate;
    
    
}


void Level::loadModels(){
    //std::string inputfile = "t-54.obj";
    //std::string inputfile = "hydra flak.obj";
    //std::string inputfile = "lancer tank.obj";
    //std::string inputfile = "T-90N.obj";
    //std::string inputfile = "Su-34_Fullback.obj";
    std::string inputfile = "B-2_Spirit.obj";
}

void Level::CrossProduct(float *a, float *b, float *normal)
{
    //Cross product formula
    normal[0] = (a[1] * b[2]) - (a[2] * b[1]);
    normal[1] = (a[2] * b[0]) - (a[0] * b[2]);
    normal[2] = (a[0] * b[1]) - (a[1] * b[0]);
    
}

void Level::updatePointNormal(float *normal, int vertex, int shape){
    float x = normals[vertex * 3];
    float y = normals[vertex * 3 + 1];
    float z = normals[vertex * 3 + 2];
    float x1 = normal[0];
    float y1 = normal[1];
    float z1 = normal[2];
        
    float x2 = (x1 + x);
    float y2 = (y1 + y);
    float z2 = (z1 + z);
        
    normals[vertex*3] = x2;
    normals[vertex*3 + 1] = y2;
    normals[vertex*3 + 2] = z2;
}


