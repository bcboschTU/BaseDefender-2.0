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
#include "Camera.hpp"
#include "GLFWBackend.h"
#include "UtilFunctions.h"
#include "Mesh.h"
#include "Renderer.h"
#include "LightingTechnique.h"
#include "Level.h"
#include "GameState.h"


const glm::vec2 SCREEN_SIZE(1024, 768);

glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
glm::mat4 MVP;
glm::mat3 ModelView3x3Matrix;

GLuint programID;
GLuint MatrixID;
GLuint ViewMatrixID;
GLuint ModelMatrixID;

GLFWwindow* window;

//buffers

float rotate = 0;

GLuint DiffuseTexture;
GLuint DiffuseTextureID;
GLuint NormalTexture;
GLuint NormalTextureID;

LightingTechnique* lightingEffect;
DirectionalLight directionalLight;

GLuint LightID1;
glm::vec3 lightPos1;

Camera camera;

GameState gamestate;
Level level;
int width = 1100;
int height = 700;

Mesh mesh;

void setupMesh(){
}


void loadTextures(){
    DiffuseTexture = loadBMP_custom("B-2_Spirit_P01.bmp");
    //DiffuseTexture = loadBMP_custom("metal.bmp");
    DiffuseTextureID  = glGetUniformLocation(programID, "myTextureSampler");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, DiffuseTexture);
    glUniform1i(DiffuseTextureID, 0);
}

void initApp(){
    level = Level(0, width, height);
    gamestate.setGameState(1);
    
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
    
    lightingEffect->SetTextureUnit(0);
    
    
    // Create and compile our GLSL program from the shaders
    //programID = LoadShaders( "lighting.vs", "lighting.fs" );
    
    // Get a handle for our "MVP" uniform
    //MatrixID = glGetUniformLocation(programID, "MVP");
    //ViewMatrixID = glGetUniformLocation(programID, "V");
    //ModelMatrixID = glGetUniformLocation(programID, "M");
    
    
    lightingEffect->Enable();
    
    lightingEffect->SetDirectionalLight(directionalLight);
    
    PointLight pl[20];
    pl[0].DiffuseIntensity = 2.0f;
    pl[0].Color = glm::vec3(1.0f, 0.0f, 0.0f);
    pl[0].Position = glm::vec3(-3.0f, 1.0f, 1.0);
    pl[0].Attenuation.Linear = 0.1f;
    
    lightingEffect->SetPointLights(1, pl);
    
    
    SpotLight sl[2];
    sl[0].DiffuseIntensity = 2.0f;
    sl[0].Color = glm::vec3(1.0f, 1.0f, 1.0f);
    sl[0].Position = camera.position();
    sl[0].Direction = camera.getTarget();
    sl[0].Attenuation.Linear = 0.1f;
    sl[0].Cutoff = 10.f;
    
    lightingEffect->SetSpotLights(1, sl);
    
    lightingEffect->SetMatSpecularIntensity(2.0f);
    lightingEffect->SetMatSpecularPower(128);
    
    return true;
}


void drawScene(){
    level.drawLevel(&camera, lightingEffect);
    glfwSwapBuffers(window);
    glfwPollEvents();
//    drawHud();
}


// update the scene based on the time elapsed since last update
void updateCamera(float secondsElapsed) {
    camera.updateCamera(secondsElapsed, window);
}

void AppMain() {
    // Initialise GLFW
    window = GLFWBackendInit(window, SCREEN_SIZE);
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    setupMesh();
    
    camera = Camera();
    
    initApp();
    
    loadTextures();
    //loadModel();
    //bindBuffer();
    
    double lastTime = glfwGetTime();
    do{
        double thisTime = glfwGetTime();
        updateCamera((float)(thisTime - lastTime));
        lastTime = thisTime;
        
        drawScene();
        drawFps(window);
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
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

