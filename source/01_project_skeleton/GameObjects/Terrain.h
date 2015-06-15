//
//  Terrain.h
//  opengl-series
//
//  Created by Bert Bosch on 15-06-15.
//
//

#ifndef __opengl_series__Terrain__
#define __opengl_series__Terrain__

#include <stdio.h>
#include <vector>
#include <cstring>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Terrain{
public:
    Terrain();
    float rand_FloatRange(float a, float b, bool between);
    void updatePointNormal(float *normal, int vertex);
    
    void generateObject();
    void writeObjFile();
    
    std::vector<float> getVertices();
    std::vector<float> getNormals();
    std::vector<float> getUv();
    std::vector<unsigned int> getFaces();
private:
    int NbVertX=20, NbVertY=20;
    double offsetX = -9.5;
    double offsetY = -6;
    //vertices
    std::vector<float> SurfaceVertices3f;
    //normals
    std::vector<float> SurfaceNormals3f;
    //colors
    std::vector<float> SurfaceColors3f;
    //tex coords
    std::vector<float> SurfaceTexCoords2f;
    
    
    std::vector<unsigned int> SurfaceTriangles3ui;
};

#endif /* defined(__opengl_series__Terrain__) */
