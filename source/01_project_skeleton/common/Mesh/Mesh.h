//
//  Mesh.h
//  opengl-series
//
//  Created by Bert Bosch on 24-03-15.
//
//

#ifndef __opengl_series__Mesh__
#define __opengl_series__Mesh__

#include <stdio.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "vboindexer.hpp"
#include "objloader.hpp"
#include "tangentspace.hpp"
#include "matrix_transform.hpp"

class Mesh{
public:
    Mesh();
    void loadModel(const char* modelName);
    void loadModelTerrain(std::vector<float> vertices,std::vector<float>uvs,std::vector<float>normals,std::vector<unsigned int> faces);
    void bindBuffers();
    void enableRender();
    void disableRender();
    void setModelMatrix(glm::mat4 _modelMatrix);
    glm::mat4 getModelMatrix();
    void rotate(glm::vec3 vector, float rot);
    void translate(glm::vec3 _trans);
    void scale(glm::vec3 _scale);
    GLuint* getVertexBuffer();
    GLuint* getUvBuffer();
    GLuint* getNormalBuffer();
    GLuint* getTangentBuffer();
    GLuint* getBitangentBuffer();
    GLuint* getElementBuffer();
    std::vector<unsigned short> getIndices();
private:
    glm::mat4 modelMatrix;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;
    std::vector<unsigned short> indices;
    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec2> indexed_uvs;
    std::vector<glm::vec3> indexed_normals;
    std::vector<glm::vec3> indexed_tangents;
    std::vector<glm::vec3> indexed_bitangents;
    
    GLuint VertexArrayID;
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint normalbuffer;
    GLuint tangentbuffer;
    GLuint bitangentbuffer;
    GLuint elementbuffer;
};

#endif /* defined(__opengl_series__Mesh__) */
