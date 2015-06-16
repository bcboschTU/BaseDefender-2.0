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

void Mesh::loadModelTerrain(std::vector<float> _vertices,std::vector<float> _uvs,std::vector<float> _normals,std::vector<unsigned int> _faces){
    

    
    for(int i = 0; i < _faces.size(); i++){
        glm::vec3 temp = glm::vec3(_vertices[3*_faces[i]], _vertices[3*_faces[i]+1],_vertices[3*_faces[i]+2]);
        //glm::vec3 temp = glm::vec3(_vertices[i], _vertices[i+1],_vertices[i+2]);
//        printf(" %u", _faces[i]);
//        printf(" %u", _faces[i+1]);
//        printf(" %u\n", _faces[i+2]);
        
        vertices.push_back(temp);
    }
    
    
    float smallestX = INFINITY;
    float smallestY = INFINITY;
    float biggestX = -INFINITY;
    float biggestY = -INFINITY;
    
    for(int i = 0; i < _uvs.size(); i = i + 2){
        if(_uvs[i]<smallestX)
            smallestX = _uvs[i];
        if(_uvs[i+1]<smallestY)
            smallestY = _uvs[i+1];
        
        if(_uvs[i]>biggestX)
            biggestX = _uvs[i];
        if(_uvs[i+1]>biggestY)
            biggestY = _uvs[i+1];
    }
    
    for(int i = 0; i < _uvs.size(); i = i + 2){
        _uvs[i] = (_uvs[i] - smallestX)/(biggestX - smallestX);
        _uvs[i+1] = (_uvs[i+1] - smallestY)/(biggestY - smallestY);
    }
    
    
    for(int i = 0; i<_faces.size(); i++){
        glm::vec2 temp = glm::vec2(_uvs[2*_faces[i]], _uvs[2*_faces[i]+1]);
        uvs.push_back(temp);
    }
    
    for(int i = 0; i < _faces.size(); i++){
        glm::vec3 temp = glm::vec3(_normals[3*_faces[i]], _normals[3*_faces[i]+1], _normals[3* _faces[i]+2]);
        normals.push_back(temp);
    }
    
    
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
