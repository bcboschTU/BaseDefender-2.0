//
//  Level.cpp
//  opengl-series
//
//  Created by Bert Bosch on 05-06-15.
//
//

#include <fstream>

#include "Level.h"

Level::Level(){
    
}

//level constructor
Level::Level(int _type, int _width, int _height){
    type = _type;
    loadLevel();
    pause = false;
    lastTimeLevel = glfwGetTime();
    lastTimePause = glfwGetTime();
    
    width = _width;
    height =_height;
}

Level::Level(int _type, int _width, int _height, const char *filename){
    type = _type;
    loadLevelFromFile(filename);
    loadLevel(); // TODO: remove when finished
    pause = false;
    lastTimeLevel = glfwGetTime();
    lastTimePause = glfwGetTime();
    
    width = _width;
    height =_height;
}


// init parameters of the level
//init positions of each mesh
void Level::loadLevel(){
    score = 0;
    multiplierBaseScore = 0;
    multiplier = 1;
    round = 1;
    roundStart(1);
    roundStartShowText = true;
    roundStartShowTextTimer = glfwGetTime();
    roundStartShowTextTime = 2.0;
    
    setupMeshes();
    initLightingEffect();
    loadTextures();
    
    
    
    Player player1 = Player("Player1", 200, 30, 10, 4, 4, 0, 1);
    players.push_back(player1);
    
    
    //base1 init
    Base base1 = Base("Base1", 500, 0, 0, 0.8, 0.8, 0, 1);
    bases.push_back(base1);
    
    
    Turret turret11 = Turret("Turret1Base1", 100, 11, 11, 0.15, 0.15, 45, 1, 10, 80, NORMAL);
    turrets.push_back(turret11);
}


void Level::loadLevelFromFile(const char *filename) {
    printf("Loading Level file %s...\n", filename);
    
    std::ifstream file(filename);
    std::string word, _name;
    
    int _hp, _level;
    float _xPos, _yPos, _width, _height, _angle;
    
    while(file >> word) {
        if(word.compare("level") == 0){
            std::string _roundStartShowTextString;
            int _score, _multiplierBaseScore, _multiplier, _round;
            bool _roundStartShowText;
            float _roundStartShowTextTime;
            
            file >> _score >> _multiplierBaseScore >> _multiplier >> _round >> _roundStartShowTextString >> _roundStartShowTextTime;
            
            _roundStartShowText = (_roundStartShowTextString.compare("true") == 0) ? true : false;
            
            printf("======== Level =========\n");
            printf("score        = %i\n", _score);
            printf("multiplierB  = %i\n", _multiplierBaseScore);
            printf("multiplier   = %i\n", _multiplier);
            printf("round        = %i\n", _round);
            printf("showText     = %s\n", _roundStartShowTextString.c_str());
            printf("showTextTime = %f\n", _roundStartShowTextTime);
            printf("========================\n");
            
        } else if(word.compare("player") == 0){
            file >> _name >> _hp >> _xPos >> _yPos >> _width >> _height >> _angle >> _level;
            
            printf("======== Player ========\n");
            printf("name        = %s\n", _name.c_str());
            printf("hp          = %i\n", _hp);
            printf("xPos        = %f\n", _xPos);
            printf("yPos        = %f\n", _yPos);
            printf("width       = %f\n", _width);
            printf("height      = %f\n", _height);
            printf("angle       = %f\n", _angle);
            printf("level       = %i\n", _level);
            printf("========================\n");

        } else if(word.compare("base") == 0) {
            file >> _name >> _hp >> _xPos >> _yPos >> _width >> _height >> _angle >> _level;
            
            printf("========= Base =========\n");
            printf("name        = %s\n", _name.c_str());
            printf("hp          = %i\n", _hp);
            printf("xPos        = %f\n", _xPos);
            printf("yPos        = %f\n", _yPos);
            printf("width       = %f\n", _width);
            printf("height      = %f\n", _height);
            printf("angle       = %f\n", _angle);
            printf("level       = %i\n", _level);
            printf("=======================\n");
            
        } else if(word.compare("turret") == 0) {
            std::string _weaponType;
            float _rangeBegin, _rangeEnd;
            file >> _name >> _hp >> _xPos >> _yPos >> _width >> _height >> _angle >> _level >> _rangeBegin >> _rangeEnd >> _weaponType;
            
            WeaponType _type;
            if(_weaponType.compare("NORMAL") == 0) {
                _type = NORMAL;
            } else if(_weaponType.compare("EXPLOSIVE") == 0) {
                _type = EXPLOSIVE;
            } else if(_weaponType.compare("DUAL") == 0) {
                _type = DUAL;
            } else if(_weaponType.compare("ROCKET") == 0) {
                _type = ROCKET;
            } else if(_weaponType.compare("NUKE") == 0) {
                _type = NUKE;
            }
            
            printf("======== Turret ========\n");
            printf("name        = %s\n", _name.c_str());
            printf("hp          = %i\n", _hp);
            printf("xPos        = %f\n", _xPos);
            printf("yPos        = %f\n", _yPos);
            printf("width       = %f\n", _width);
            printf("height      = %f\n", _height);
            printf("angle       = %f\n", _angle);
            printf("level       = %i\n", _level);
            printf("rangeBegin  = %f\n", _rangeBegin);
            printf("rangeEnd    = %f\n", _rangeEnd);
            printf("weaponType  = %s (%i)\n", _weaponType.c_str(), _type);
            printf("=======================\n");
            
        } else if(word.compare("enemie") == 0){
            file >> _name >> _hp >> _xPos >> _yPos >> _width >> _height >> _angle >> _level;
            
            printf("======== Enemie ========\n");
            printf("name        = %s\n", _name.c_str());
            printf("hp          = %i\n", _hp);
            printf("xPos        = %f\n", _xPos);
            printf("yPos        = %f\n", _yPos);
            printf("width       = %f\n", _width);
            printf("height      = %f\n", _height);
            printf("angle       = %f\n", _angle);
            printf("level       = %i\n", _level);
            printf("========================\n");
            
        }
    }
    
    printf("Loading done.\n");
}


// update the scene based on the time elapsed since last update
// free flight camera controlls
void Level::updateCamera(float secondsElapsed, GLFWwindow* window) {
    //rotate the cube
    const GLfloat degreesPerSecond = 180.0f;
    gDegreesRotated += secondsElapsed * degreesPerSecond;
    while(gDegreesRotated > 360.0f) gDegreesRotated -= 360.0f;
    
    //move position of camera based on WASD keys, and XZ keys for up and down
    const float moveSpeed = 20.0; //units per second
    if(glfwGetKey(window, 'S')){
        camera.offsetPosition(secondsElapsed * moveSpeed * -camera.forward());
    } else if(glfwGetKey(window, 'W')){
        camera.offsetPosition(secondsElapsed * moveSpeed * camera.forward());
    }
    if(glfwGetKey(window, 'A')){
        camera.offsetPosition(secondsElapsed * moveSpeed * -camera.right());
    } else if(glfwGetKey(window, 'D')){
        camera.offsetPosition(secondsElapsed * moveSpeed * camera.right());
    }
    if(glfwGetKey(window, 'Z')){
        camera.offsetPosition(secondsElapsed * moveSpeed * -glm::vec3(0,1,0));
    } else if(glfwGetKey(window, 'X')){
        camera.offsetPosition(secondsElapsed * moveSpeed * glm::vec3(0,1,0));
    }
    else if(glfwGetKey(window, 'P')){
        camera.setInputTrue(!camera.getInputTrue());
    }
    
    //rotate camera based on mouse movement
    const float mouseSensitivity = 0.1f;
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    camera.offsetOrientation(mouseSensitivity * (float)mouseY, mouseSensitivity * (float)mouseX);
    glfwSetCursorPos(window, 0, 0); //reset the mouse, so it doesn't go out of the window
    
    //increase or decrease field of view based on mouse wheel
    const float zoomSensitivity = -0.2f;
    float fieldOfView = camera.fieldOfView() + zoomSensitivity * (float)gScrollY;
    if(fieldOfView < 5.0f) fieldOfView = 5.0f;
    if(fieldOfView > 130.0f) fieldOfView = 130.0f;
    camera.setFieldOfView(fieldOfView);
    gScrollY = 0;
}

// mouse scroll function
void Level::OnScroll(GLFWwindow* window, double deltaX, double deltaY) {
    gScrollY += deltaY;
}


//return camera object
Camera Level::getCamera(){
    return camera;
}


//render all the meshes on there positions.
void Level::drawLevel(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glClearColor(0.2f, 0.2f, 0.4f, 0.0f);
    
    
    if(!pause){
        //update all the vector array elements first
        updateLevel();
    }
    
    // Clear the screen
   
    
    updateLighting();
    
    
    //turrets rendering
    lightingEffect->SetTextId(1);
    turretMesh.enableRender();
    for (int i = 0; i<turrets.size(); i++) {
        Turret * turret = &turrets[i];
        drawMesh(turretMesh, &camera, lightingEffect, turret->getMesh().getModelMatrix());
    }
    turretMesh.disableRender();
    
    
    //renderBase
    baseMesh.enableRender();
    for (int i = 0; i< bases.size(); i++) {
        Base * base = &bases[i];
        Mesh tempMesh = base->getMesh();
        drawMesh(baseMesh, &camera, lightingEffect, tempMesh.getModelMatrix());
    }
    baseMesh.disableRender();
    
    
    
    //player rendering
    lightingEffect->SetTextId(0);
    playerMesh.enableRender();
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        Mesh tempMesh = player->getMesh();
        drawMesh(playerMesh, &camera, lightingEffect, tempMesh.getModelMatrix());
    }
    playerMesh.disableRender();
    
    
    lightingEffect->SetTextId(2);
    enemyMesh_100_50.enableRender();
    for (int i = 0; i<enemies.size(); i++) {
        Enemie * enemie = &enemies[i];
        if(enemie->getHp() > 25){
            Mesh tempMesh = enemie->getMesh();
            drawMesh(enemyMesh_100_50, &camera, lightingEffect, tempMesh.getModelMatrix());
        }
    }
    enemyMesh_100_50.disableRender();
    
    enemyMesh_50_0.enableRender();
    for (int i = 0; i<enemies.size(); i++) {
        Enemie * enemie = &enemies[i];
        if(enemie->getHp() > 0 && enemie->getHp() < 25){
            Mesh tempMesh = enemie->getMesh();
            drawMesh(enemyMesh_50_0, &camera, lightingEffect, tempMesh.getModelMatrix());
        }
    }
    enemyMesh_50_0.disableRender();
    
    
    bulletMesh.enableRender();
    for (int i = 0; i<bullets.size(); i++) {
        Bullet *bullet = bullets[i];
        bool drawable = bullet->getDrawAble();
        if(drawable){
            Mesh tempMesh = bullet->getMesh();
            drawMesh(bulletMesh, &camera, lightingEffect, tempMesh.getModelMatrix());
        }
    }
    bulletMesh.disableRender();    
    
    
    explosionMesh.enableRender();
    for (int i = 0; i<explosions.size(); i++) {
        Explosion *explosion = &explosions[i];
        bool drawable = explosion->getDrawAble();
        if(drawable){
            Mesh tempMesh = explosion->getMesh();
            drawMesh(explosionMesh, &camera, lightingEffect, tempMesh.getModelMatrix());
        }
    }
    explosionMesh.disableRender();
}


// Gives the shader program the matrixes to compute the right position and lighting
void Level::drawMesh(Mesh mesh, Camera* camera, LightingTechnique *lightingEffect, glm::mat4 _Model) {
    Projection = camera->projection();
    View = camera->view();
    MVP = Projection * View * _Model;
    lightingEffect->SetMatrix(MVP);
    
    lightingEffect->SetViewMatrix(View);
    
    lightingEffect->SetModeldMatrix(_Model);
    
    Rederer(&mesh);
}

//loading of the meshes for each of the objects types
void Level::setupMeshes(){
    std::string playerStr = "player.obj";
    std::string baseStr = "sphere.obj";
    std::string turretstr = "turret.obj";
    std::string enemystr_100_50 = "B-2_Spirit.obj";
    std::string enemystr_50_0 = "blox.obj";
    std::string bulletstr = "bullet.obj";
    std::string explosionstr = "sphere.obj";
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    //playermesh
    playerMesh =  Mesh();
    const char * model = playerStr.c_str();
    playerMesh.loadModel(model);
    playerMesh.bindBuffers();
    
    
    baseMesh =  Mesh();
    model = baseStr.c_str();
    baseMesh.loadModel(model);
    baseMesh.bindBuffers();
    
    turretMesh =  Mesh();
    model = turretstr.c_str();
    turretMesh.loadModel(model);
    turretMesh.bindBuffers();
    
    
    enemyMesh_100_50 =  Mesh();
    model = enemystr_100_50.c_str();
    enemyMesh_100_50.loadModel(model);
    enemyMesh_100_50.bindBuffers();
    
    enemyMesh_50_0 =  Mesh();
    model = enemystr_50_0.c_str();
    enemyMesh_50_0.loadModel(model);
    enemyMesh_50_0.bindBuffers();
    
    bulletMesh =  Mesh();
    model = bulletstr.c_str();
    bulletMesh.loadModel(model);
    bulletMesh.bindBuffers();
    
    explosionMesh =  Mesh();
    model = explosionstr.c_str();
    explosionMesh.loadModel(model);
    explosionMesh.bindBuffers();
}

//delete the textures from memory
void Level::cleanup(){
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);
    
    glDeleteTextures(1, &DiffuseTexturePlayer);
    //glDeleteTextures(1, &NormalTexture);
    //glDeleteTextures(1, &SpecularTexture);
}


// loading of the textures for each mesh type
void Level::loadTextures(){
    
    DiffuseTexturePlayer = loadBMP_custom("Su-34_Fullback_P01.bmp");
    DiffuseTextureTurret = loadBMP_custom("B-2_Spirit_P01.bmp");
    DiffuseTextureEnemie = loadBMP_custom("city.bmp");
    
    lightingEffect->addTexture(DiffuseTexturePlayer, 0);
    lightingEffect->addTexture(DiffuseTextureTurret, 1);
    lightingEffect->addTexture(DiffuseTextureEnemie, 2);
    
    //DiffuseTexture = loadBMP_custom("metal.bmp");
    
    /*
    DiffuseTexturePlayerID  = glGetUniformLocation(programID, "myTextureSampler");
    
    glUniform1i(DiffuseTexturePlayerID, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, DiffuseTexturePlayer);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glUniform1i(DiffuseTexturePlayerID, 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, DiffuseTextureEnemie);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    */
    
}


// positions of the lights.
void Level::initLightingEffect(){
    lightingEffect = NULL;
    
    lightingEffect = new LightingTechnique();
    
    directionalLight.Color = glm::vec3(1.0f, 1.0f, 1.0f);
    directionalLight.AmbientIntensity = 0.19f;
    directionalLight.DiffuseIntensity = 0.75f;
    directionalLight.Direction = glm::vec3(1.0f, 0.0, 1.0);
    
    std::cout <<lightingEffect->Init();
    if (!lightingEffect->Init())
    {
        return false;
    }
    
    lightingEffect->Enable();
    
    
    //switching function for textures
    lightingEffect->SetTextureUnit(0);
    
    
    return true;
}

// update light positions for each frame
void Level::updateLighting(){
    lightingEffect->Enable();
    
    lightingEffect->SetDirectionalLight(directionalLight);
    
    PointLight pl[20];
    pl[0].DiffuseIntensity = 2.0f;
    pl[0].Color = glm::vec3(1.0f, 0.0f, 0.0f);
    pl[0].Position = glm::vec3(-30.0f, 10.0f, -190.0);
    pl[0].Attenuation.Linear = 0.1f;
    
    lightingEffect->SetPointLights(1, pl);
    
    
    SpotLight sl[2];
    sl[0].DiffuseIntensity = 2.0f;
    sl[0].Color = glm::vec3(1.0f, 1.0f, 1.0f);
    sl[0].Position = camera.position();
    sl[0].Direction = camera.getTarget();
    sl[0].Attenuation.Linear = 0.1f;
    sl[0].Cutoff = 10.f;
    
    /*
    sl[1].DiffuseIntensity = 2.9f;
    sl[1].Color = glm::vec3(1.0f, 0.0f, 0.0f);
    sl[1].Position = glm::vec3(0.0f, 1.0f, 0.0f);
    sl[1].Direction = glm::vec3(0.0f, 0.0f, -1.0f);
    sl[1].Attenuation.Linear = 0.1f;
    sl[1].Cutoff = 20.0f;
     */
    lightingEffect->SetSpotLights(1, sl);
    
    
    lightingEffect->SetMatSpecularIntensity(2.0f);
    lightingEffect->SetMatSpecularPower(128);
}


// updates the level objects each frame.
void Level::updateLevel(){
    checkIfGameOver();
    //clear all the bullets from last frame
    checkRoundUpdate();
    checkMultiplerScore();
    
    bullets.clear();
    //quadtree.empty();
    //get all bullets:
    
    //update the turrets targets
    for (int i = 0; i< turrets.size(); i++){
        Turret *turret = &turrets[i];
        turret->setTarget(&enemies);
    }
    
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
    
    
    for(int i = 0; i<explosions.size(); i++){
        Explosion * explosion = &explosions[i];
        explosion->updateExplosion();
    }
}

// get the bullets from all the players and turrets, stores it in one vector
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


//per bullet is calculated if it hits an enemy
//TODO: if enemies also shoot, calculate hit
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

// no idea.. old code maybe -> TODO: check if called
void Level::checkIfBulletsHitEnemy(int begin, int end){
    
}


// calculates if the player/turret/base is hit by an enemy
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

// level round management
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

//multiple for no hit streak
void Level::checkMultiplerScore(){
    if(score - multiplierBaseScore > (100 * multiplier)){
        multiplierBaseScore = score;
        multiplier++;
    }
}

//update the vector that holds all the enemies, if enemy is dead, delete from vector
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


//returns the player on pos i
Player* Level::getPlayer(int i){
    return &players[i];
}


// gives a randon value between a and b, if bool is true -> values between 100 and -100 are excluded
// TODO: replace between by 2 values
// TODO: transfer function to util class
float Level::rand_FloatRange(float a, float b, bool between){
    float randomValue = ((b-a)*((float)rand()/RAND_MAX))+a;
    if (between) {
        if(randomValue > 100 || randomValue < -100){
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


// generates the enemies for each round
void Level::generateEnemies(){
    if(!roundStartShowText){
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTimeLevel);
        if(deltaTime > enemySpawnRate && enemyAmount > 0){
            for(int i = 0; i< enemySpawnLoop; i++){
                float xPos = rand_FloatRange(-140,140, true);
                float yPos = rand_FloatRange(-140,140, false);
                Enemie enemie = Enemie("enemie", 50, xPos, yPos, 5, 5, 0, 1);
                enemie.setTargetPlayer(&players[0]);
                //enemie.setTargetBase(&bases[0]);
                enemies.push_back(enemie);
                lastTimeLevel = currentTime;
                enemyAmount--;
            }
        }
    }
}

// sets the game on pause + resets the time if unpaused
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

// checks if an friendly unit is dead, if dead reset level
void Level::checkIfGameOver(){
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        if(player->getHp() <= 0){
            resetLevel();
        }
    }
    
    for (int i = 0; i<bases.size(); i++) {
        Base * base = &bases[i];
        if(base->getHp() <= 0){
            resetLevel();
        }
    }
}


//clears all the vectors and the loads the level again
void Level::resetLevel(){
    players.clear();
    bullets.clear();
    bases.clear();
    turrets.clear();
    enemies.clear();
    explosions.clear();
    //    cleanUp();
    loadLevel();
}


// function to render a 2d string on screen
void Level::renderString(float x, float y, void *font, const std::string &string)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    for (int n=0; n<string.size(); ++n) {
        //glutBitmapCharacter(font, string[n]);
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
    int amountOfEnemy = 6;
    enemyAmount = amountOfEnemy * _round;
    int rate = (int)sqrt(_round);
    enemySpawnRate = 0.4 - (round/100)*2;
    enemySpawnLoop = 2 * rate;
    
    
}

