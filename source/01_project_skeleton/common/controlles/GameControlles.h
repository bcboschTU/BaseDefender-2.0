//
//  Camera2.h
//  opengl-series
//
//  Created by Bert Bosch on 07-06-15.
//
//

#ifndef __opengl__controls__
#define __opengl__controls__

#include <iostream>
#include "matrix_transform.hpp"
#include "Level.h"
#include "GameState.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"


class GameControlles {
public:
    GameControlles();
    const glm::vec3& getPosition() const;
    void setPosition(const glm::vec3& position);
    void lookAt(glm::vec3 position);
    void computeInputs(GLFWwindow* window,Level *level,GameState* gamestate);
    void computeInputsMouse(GLFWwindow* window,Level *level,GameState* gamestate);
    
    void computeInputsGame(GLFWwindow* window,Level *level,GameState* gamestate);
    void computeInputsGameMouse(GLFWwindow* window,Level *level,GameState* gamestate);
    
    void computeInputsMenu(GLFWwindow* window,Level *level,GameState* gamestate);
    void computeInputsMenuMouse(GLFWwindow* window,Level *level,GameState* gamestate);
    
    glm::vec3 getMouseWorldPos(GLFWwindow* window);
    
    bool getInputTrue();
    void setInputTrue(bool input);
    
    
private:
    glm::vec3 _position;
    float _minZoom;
    float _maxZoom;
    int width = 1100;
    int height = 700;
    
    bool _inputBool = true;
    
    float _horizontalAngle;
    float _verticalAngle;
    float _fieldOfView;
    float _nearPlane;
    float _farPlane;
    float _viewportAspectRatio;
};

#endif /* defined(__opengl_series__Camera2__) */
