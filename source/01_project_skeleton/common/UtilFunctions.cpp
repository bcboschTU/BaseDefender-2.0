//
//  UtilFunctions.cpp
//  opengl-series
//
//  Created by Bert Bosch on 24-03-15.
//
//

#include "UtilFunctions.h"

void drawFps(GLFWwindow* pWindow){
    // Measure speed
    static int nbFrames = 0;
    static double lastTimeFps = glfwGetTime();
    double currentTime = glfwGetTime();
    double delta = currentTime - lastTimeFps;
    nbFrames++;
    if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago
        double fps = double(nbFrames) / delta;
        
        std::stringstream ss;
        ss << "Base Defender Version 0.1" << " [" << fps << " FPS]";
        
        glfwSetWindowTitle(pWindow, ss.str().c_str());
        
        nbFrames = 0;
        lastTimeFps = currentTime;
    }
}