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





const glm::vec2 SCREEN_SIZE(1024, 768);

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


void initApp(){
    
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
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    level = Level(0, SCREEN_SIZE[0],SCREEN_SIZE[1]);
    
    initApp();
    
    double lastTime = glfwGetTime();
    do{
        double thisTime = glfwGetTime();
        level.updateCamera((float)(thisTime - lastTime), window);
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

