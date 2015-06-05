//
//  GLFWBackend.h
//  opengl-series
//
//  Created by Bert Bosch on 24-03-15.
//
//

#ifndef __opengl_series__GLFWBackend__
#define __opengl_series__GLFWBackend__

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

GLFWwindow* GLFWBackendInit(GLFWwindow* gWindow, glm::vec2 SCREEN_SIZE);

void initGL();

#endif /* defined(__opengl_series__GLFWBackend__) */
