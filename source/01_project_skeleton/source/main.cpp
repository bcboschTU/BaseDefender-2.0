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
GLuint VertexArrayID;

float rotate = 0;

GLuint DiffuseTexture;
GLuint DiffuseTextureID;
GLuint NormalTexture;
GLuint NormalTextureID;

LightingTechnique* lightingEffect;
DirectionalLight directionalLight;

GLuint LightID1;
GLuint LightID2;
GLuint LightID3;
GLuint LightID4;
glm::vec3 lightPos1;
glm::vec3 lightPos2;
glm::vec3 lightPos3;
glm::vec3 lightPos4;

Camera camera;
double gScrollY = 0.0;
GLfloat gDegreesRotated = 0.0f;


Mesh mesh;
Mesh mesh2;
Mesh mesh3;
Mesh mesh4;
Mesh mesh5;

void cleanUp(){
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);
    
    glDeleteTextures(1, &DiffuseTexture);
    //glDeleteTextures(1, &NormalTexture);
    //glDeleteTextures(1, &SpecularTexture);
}

void setupMesh(){
    std::string str = "B-2_Spirit.obj";
    std::string str2 = "sphere.obj";
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    mesh =  Mesh();
    mesh2 =  Mesh();
    mesh3 = Mesh();
    mesh4 = Mesh();
    mesh5 = Mesh();
    
    const char * model = str.c_str();
    mesh.loadModel(model);
    mesh.bindBuffers();
    
    mesh.scale(glm::vec3(0.3f, 0.3f, 0.3f));
    mesh.translate(glm::vec3(0,-1,-1));
    float rot = 270 * (M_PI/180);
    mesh.rotate(glm::vec3(1.f, 0.f, 0.f),rot);

    mesh2.translate(glm::vec3(0,2,-2));
    mesh2.scale(glm::vec3(0.1f, 0.1f, 0.1f));
    
    const char * model2 = str2.c_str();
    mesh3.loadModel(model2);
    mesh3.bindBuffers();
    
    mesh3.translate(glm::vec3(3.0f, 1.0f, 1.0));
    mesh3.scale(glm::vec3(0.1f, 0.1f, 0.1f));
    
    mesh4.translate(glm::vec3(-3.0f, 1.0f, 1.0));
    mesh4.scale(glm::vec3(0.1f, 0.1f, 0.1f));
    
    mesh5.translate(glm::vec3(1.0f, 1.0f, 1.0));
    mesh5.scale(glm::vec3(0.1f, 0.1f, 0.1f));
    
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
    
    return true;
    
    // Create and compile our GLSL program from the shaders
    //programID = LoadShaders( "lighting.vs", "lighting.fs" );
    
    // Get a handle for our "MVP" uniform
    //MatrixID = glGetUniformLocation(programID, "MVP");
    //ViewMatrixID = glGetUniformLocation(programID, "V");
    //ModelMatrixID = glGetUniformLocation(programID, "M");
}


void drawLevel(){
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glClearColor(0.2f, 0.2f, 0.4f, 0.0f);
    
    lightingEffect->Enable();
    
    lightingEffect->SetDirectionalLight(directionalLight);
    
    PointLight pl[20];
    pl[0].DiffuseIntensity = 2.0f;
    pl[0].Color = glm::vec3(1.0f, 0.0f, 0.0f);
    pl[0].Position = glm::vec3(-3.0f, 1.0f, 1.0);
    pl[0].Attenuation.Linear = 0.1f;
    
    pl[1].DiffuseIntensity = 2.0f;
    pl[1].Color = glm::vec3(0.0f, 0.0f, 1.0f);
    pl[1].Position = glm::vec3(3.0f, 1.0f, 1.0);
    pl[1].Attenuation.Linear = 0.1f;
    
    pl[2].DiffuseIntensity = 2.0f;
    pl[2].Color = glm::vec3(0.0f, 1.0f, 0.0f);
    pl[2].Position = glm::vec3(1.0f, 1.0f, 1.0);
    pl[2].Attenuation.Linear = 0.1f;
    
    lightingEffect->SetPointLights(3, pl);
    
    
    SpotLight sl[2];
    sl[0].DiffuseIntensity = 2.0f;
    sl[0].Color = glm::vec3(1.0f, 1.0f, 1.0f);
    sl[0].Position = camera.position();
    sl[0].Direction = camera.getTarget();
    sl[0].Attenuation.Linear = 0.1f;
    sl[0].Cutoff = 10.f;
    
    sl[1].DiffuseIntensity = 2.9f;
    sl[1].Color = glm::vec3(1.0f, 0.0f, 0.0f);
    sl[1].Position = glm::vec3(0.0f, 1.0f, 0.0f);
    sl[1].Direction = glm::vec3(0.0f, 0.0f, -1.0f);
    sl[1].Attenuation.Linear = 0.1f;
    sl[1].Cutoff = 20.0f;
    lightingEffect->SetSpotLights(2, sl);
    
    
    lightingEffect->SetMatSpecularIntensity(2.0f);
    lightingEffect->SetMatSpecularPower(128);
    
    
    mesh.enableRender();
    
    // MESH
    Model = mesh.getModelMatrix();
    Projection = camera.projection();
    View = camera.view();
    MVP = Projection * View * Model;
    /*
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
    */
    
    lightingEffect->SetMatrix(MVP);
    
    lightingEffect->SetViewMatrix(View);
    
    lightingEffect->SetModeldMatrix(Model);
    
    
    Rederer(&mesh);
    
    //mesh
    Model = mesh2.getModelMatrix();
    Projection = camera.projection();
    View = camera.view();
    MVP = Projection * View * Model;
    
    lightingEffect->SetMatrix(MVP);
    
    lightingEffect->SetViewMatrix(View);
    
    lightingEffect->SetModeldMatrix(Model);
    
    Rederer(&mesh);
    
    mesh.disableRender();
    
    
    mesh3.enableRender();
    //LIGHT
    Model = mesh3.getModelMatrix();
    Projection = camera.projection();
    View = camera.view();
    MVP = Projection * View * Model;
    
    lightingEffect->SetMatrix(MVP);
    
    lightingEffect->SetViewMatrix(View);
    
    lightingEffect->SetModeldMatrix(Model);
    
    Rederer(&mesh3);
    
    Model = mesh4.getModelMatrix();
    Projection = camera.projection();
    View = camera.view();
    MVP = Projection * View * Model;
    
    lightingEffect->SetMatrix(MVP);
    
    lightingEffect->SetViewMatrix(View);
    
    lightingEffect->SetModeldMatrix(Model);
    
    Rederer(&mesh3);
    
    Model = mesh5.getModelMatrix();
    Projection = camera.projection();
    View = camera.view();
    MVP = Projection * View * Model;
    
    lightingEffect->SetMatrix(MVP);
    
    lightingEffect->SetViewMatrix(View);
    
    lightingEffect->SetModeldMatrix(Model);
    
    Rederer(&mesh3);
    
    mesh3.disableRender();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}


// update the scene based on the time elapsed since last update
void updateCamera(float secondsElapsed) {
    //rotate the cube
    const GLfloat degreesPerSecond = 180.0f;
    gDegreesRotated += secondsElapsed * degreesPerSecond;
    while(gDegreesRotated > 360.0f) gDegreesRotated -= 360.0f;
    
    //move position of camera based on WASD keys, and XZ keys for up and down
    const float moveSpeed = 2.0; //units per second
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

void OnScroll(GLFWwindow* window, double deltaX, double deltaY) {
    gScrollY += deltaY;
}

void AppMain() {
    // Initialise GLFW
    window = GLFWBackendInit(window, SCREEN_SIZE);
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    setupMesh();
    
    initApp();
    
    loadTextures();
    //loadModel();
    //bindBuffer();
    
    double lastTime = glfwGetTime();
    do{
        double thisTime = glfwGetTime();
        updateCamera((float)(thisTime - lastTime));
        lastTime = thisTime;
        
        drawLevel();
        drawFps(window);
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Cleanup VBO and shader
    cleanUp();
    
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

