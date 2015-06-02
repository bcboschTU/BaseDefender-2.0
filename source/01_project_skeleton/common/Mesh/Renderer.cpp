//
//  Renderer.cpp
//  opengl-series
//
//  Created by Bert Bosch on 24-03-15.
//
//

#include "Renderer.h"

void Rederer(Mesh* mesh){
    glDrawElements(
                   GL_TRIANGLES,      // mode
                   (int)mesh->getIndices().size(),    // count
                   GL_UNSIGNED_SHORT, // type
                   (void*)0           // element array buffer offset
                   );
}


/*
 glEnableVertexAttribArray(0);
 glBindBuffer(GL_ARRAY_BUFFER, *mesh->getVertexBuffer());
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
 glBindBuffer(GL_ARRAY_BUFFER, *mesh->getUvBuffer());
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
 glBindBuffer(GL_ARRAY_BUFFER, *mesh->getNormalBuffer());
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
 glBindBuffer(GL_ARRAY_BUFFER, *mesh->getTangentBuffer());
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
 glBindBuffer(GL_ARRAY_BUFFER, *mesh->getBitangentBuffer());
 glVertexAttribPointer(
 4,                                // attribute
 3,                                // size
 GL_FLOAT,                         // type
 GL_FALSE,                         // normalized?
 0,                                // stride
 (void*)0                          // array buffer offset
 );
 // Index buffer
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *mesh->getElementBuffer());

*/