#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//include opengl:
#include <OpenGL/gl3.h>

//include glm:
#include "glm.hpp"
#include "matrix_transform.hpp"

//include common:
#include "shader.hpp"
#include "texture.hpp"
#include "controls.hpp"
#include "GLFWBackend.h"
#include "UtilFunctions.h"
#include "Mesh.h"
#include "Renderer.h"
#include "LightingTechnique.h"
#include "Level.h"
#include "GameControlles.h"
#include "GameState.h"


const glm::vec2 SCREEN_SIZE(1100, 700);

GLFWwindow* window;

float rotate = 0;

GLuint LightID1;
GLuint LightID2;
GLuint LightID3;
GLuint LightID4;
glm::vec3 lightPos1;
glm::vec3 lightPos2;
glm::vec3 lightPos3;
glm::vec3 lightPos4;

Level level;
GameControlles gameController;
GameState gamestate;

int cameraMode = 1;

void initApp(){
    level = Level(0, SCREEN_SIZE[0],SCREEN_SIZE[1],"level1.lvl");
    gamestate.setGameState(1);
    //gameController.setPosition(level.getCamera().position());
}


void drawLevel(){
    level.drawLevel();
    glfwSwapBuffers(window);
    glfwPollEvents();
}





void AppMain() {
    // Initialise GLFW
    window = GLFWBackendInit(window, SCREEN_SIZE);
    
    // Ensure we can capture the escape key being pressed below
    //glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    initApp();
    
    double lastTime = glfwGetTime();
    do{
        double thisTime = glfwGetTime();

        if(cameraMode == 1){
            gameController.computeInputsMouse(window, &level, &gamestate);        //TODO:input for game
            gameController.computeInputs(window, &level, &gamestate);             //TODO:input for game
            if(!gameController.getInputTrue()){
                cameraMode = 2;
                level.getCamera().setInputTrue(true);
                glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
            }
            
        }
        else{
            glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
            level.updateCamera((float)(thisTime - lastTime), window);
            if(!level.getCamera().getInputTrue()){
                cameraMode = 1;
                gameController.setInputTrue(true);
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
        
        lastTime = thisTime;
        
        drawLevel();
        drawFps(window);
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Cleanup VBO and shader
    level.cleanup();
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}

int main(int argc, char *argv[]) {
    try {
        AppMain();
    } catch (const std::exception& e){
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

