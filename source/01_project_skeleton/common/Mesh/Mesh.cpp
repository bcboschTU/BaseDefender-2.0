//
//  Mesh.cpp
//  opengl-series
//
//  Created by Bert Bosch on 24-03-15.
//
//

#include "Mesh.h"
Mesh::Mesh(){
    modelMatrix = glm::mat4(1.0f);;
}

void Mesh::loadModel(const char* modelName){
    //std::string inputfile = "B-2_Spirit.obj";
    
    
    //loadOBJ("Su-34_Fullback.obj", vertices, uvs, normals);
    loadOBJ(modelName, vertices, uvs, normals);
    //loadOBJ("lightning_obj.obj", vertices, uvs, normals);
    //indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);
    std::cout<< "obj load done: " << glfwGetTime() << "\n";
    computeTangentBasis(
                        vertices, uvs, normals, // input
                        tangents, bitangents    // output
                        );
    std::cout<< "computeTangentBasis load done: " << glfwGetTime() << "\n";
    indexVBO_TBN(
                 vertices, uvs, normals, tangents, bitangents,
                 indices, indexed_vertices, indexed_uvs, indexed_normals, indexed_tangents, indexed_bitangents
                 );
    std::cout<< "indexVBO_TBN load done: " << glfwGetTime() << "\n";
}

void Mesh::bindBuffers(){
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);
    
    
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);
    
    
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);
    
    
    
    glGenBuffers(1, &tangentbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_tangents.size() * sizeof(glm::vec3), &indexed_tangents[0], GL_STATIC_DRAW);
    
    
    glGenBuffers(1, &bitangentbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_bitangents.size() * sizeof(glm::vec3), &indexed_bitangents[0], GL_STATIC_DRAW);
    
    // Generate a buffer for the indices as well
    
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
}

void Mesh::enableRender(){
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0,                  // attribute
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(
                          1,                                // attribute
                          2,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    // 3rd attribute buffer : normals
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(
                          2,                                // attribute
                          3,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    
    // 4th attribute buffer : tangents
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
    glVertexAttribPointer(
                          3,                                // attribute
                          3,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    // 5th attribute buffer : bitangents
    glEnableVertexAttribArray(4);
    glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
    glVertexAttribPointer(
                          4,                                // attribute
                          3,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

}

void Mesh::disableRender(){
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
}

void Mesh::setModelMatrix(glm::mat4 _modelMatrix){
    modelMatrix = _modelMatrix;
}

glm::mat4 Mesh::getModelMatrix(){
    return modelMatrix;
}
void Mesh::rotate(glm::vec3 vector, float rot){
    modelMatrix = glm::rotate(modelMatrix,rot,vector);
}

void Mesh::translate(glm::vec3 trans){
    modelMatrix = glm::translate(modelMatrix, trans);
}
void Mesh::scale(glm::vec3 scale){
    modelMatrix = glm::scale(modelMatrix, scale);
}

GLuint* Mesh::getVertexBuffer(){
    return &vertexbuffer;
}
GLuint* Mesh::getUvBuffer(){
    return &uvbuffer;
}
GLuint* Mesh::getNormalBuffer(){
    return &normalbuffer;
}
GLuint* Mesh::getTangentBuffer(){
    return &tangentbuffer;
}
GLuint* Mesh::getBitangentBuffer(){
    return &bitangentbuffer;
}
GLuint* Mesh::getElementBuffer(){
    return &elementbuffer;
}

std::vector<unsigned short> Mesh::getIndices(){
    return indices;
}
