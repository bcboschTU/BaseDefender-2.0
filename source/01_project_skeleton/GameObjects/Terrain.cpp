//
//  Terrain.cpp
//  opengl-series
//
//  Created by Bert Bosch on 15-06-15.
//
//

#include "Terrain.h"

Terrain::Terrain(){
    
}

float Terrain::rand_FloatRange(float a, float b, bool between){
    float randomValue = ((b-a)*((float)rand()/RAND_MAX))+a;
    if (between) {
        if(randomValue > 10 || randomValue < -10){
            return randomValue;
        }
        else{
            return rand_FloatRange(a,b, between);
        }
    }
    else{
        return randomValue;
    }
}

void CrossProduct(float *a, float *b, float *normal)
{
    //Cross product formula
    normal[0] = (a[1] * b[2]) - (a[2] * b[1]);
    normal[1] = (a[2] * b[0]) - (a[0] * b[2]);
    normal[2] = (a[0] * b[1]) - (a[1] * b[0]);
    
}

void Terrain::updatePointNormal(float *normal, int vertex){
    if(SurfaceNormals3f[vertex*3] == -100 && SurfaceNormals3f[vertex*3 + 1] == -100 && SurfaceNormals3f[vertex*3 + 2] == -100){
        SurfaceNormals3f[vertex*3] = normal[0];
        SurfaceNormals3f[vertex*3 + 1] = normal[1];
        SurfaceNormals3f[vertex*3 + 2] = normal[2];
    }
    else{
        float x = SurfaceNormals3f[vertex * 3];
        float y = SurfaceNormals3f[vertex * 3 + 1];
        float z = SurfaceNormals3f[vertex * 3 + 2];
        float x1 = normal[0];
        float y1 = normal[1];
        float z1 = normal[2];
        
        float x2 = (x1 + x);
        float y2 = (y1 + y);
        float z2 = (z1 + z);
        
        SurfaceNormals3f[vertex*3] = x2;
        SurfaceNormals3f[vertex*3 + 1] = y2;
        SurfaceNormals3f[vertex*3 + 2] = z2;
    }
}

void Terrain::generateObject(){
    
    SurfaceVertices3f.resize(3*NbVertX*NbVertY);
    //normals with 3 coordinates
    SurfaceNormals3f.resize(3*NbVertX*NbVertY);
    //texture coords per vertex
    SurfaceTexCoords2f.resize(2*NbVertX*NbVertY);
    //triangles (2 per default)
    // given random NbVertX and NbVertY calculate amount of triangles that can be created.
    SurfaceTriangles3ui.resize(3*2*(NbVertX-1)*(NbVertY-1));
    //per vertex colors
    SurfaceColors3f.resize(3*NbVertX*NbVertY);
    
    int vertexCount = 0;
    int textureCount = 0;
    float width = 0.05;
    float height = 0.065;
    for(double i = offsetX; i < NbVertX + offsetX; i++) {
        for(double j = offsetY; j< NbVertY + offsetY; j++) {
            SurfaceVertices3f[vertexCount]=(float)i /width;
            SurfaceVertices3f[vertexCount+1]=(float)j / height;
            //float randomX = (i + (rand() * i));
            //float randomY = (j + (rand() * j));
            float heightX = rand_FloatRange(0.05,5,false);
            float heightY = rand_FloatRange(0.05,5,false);
            SurfaceVertices3f[vertexCount+2]= (-cosf(0.1*(float)i)/heightX - sinf(0.1*(float)j)/heightY) -203;
            //SurfaceVertices3f[vertexCount+2]= -203;
            
            SurfaceNormals3f[vertexCount]= -100;
            SurfaceNormals3f[vertexCount+1]= -100;
            SurfaceNormals3f[vertexCount+2]= -100;
            
            if(SurfaceVertices3f[vertexCount+2] <= -0.1){
                SurfaceColors3f[vertexCount]= 0;
                SurfaceColors3f[vertexCount+1]= 0;
                SurfaceColors3f[vertexCount+2]= 1;
            }
            else if(SurfaceVertices3f[vertexCount+2] > -0.1 && SurfaceVertices3f[vertexCount+2] < 0.1){
                SurfaceColors3f[vertexCount]= 0;
                SurfaceColors3f[vertexCount+1]= 1;
                SurfaceColors3f[vertexCount+2]= 0;
            }
            else{
                SurfaceColors3f[vertexCount]= 1;
                SurfaceColors3f[vertexCount+1]= 1;
                SurfaceColors3f[vertexCount+2]= 1;
            }
            
            SurfaceTexCoords2f[textureCount]= (float)i/width;
            SurfaceTexCoords2f[textureCount+1]= (float)j/height;
            
            vertexCount += 3;
            textureCount += 2;
        }
    }
    
    int triangleCount = 0;
    for(double i = 0; i < NbVertX-1; i++) {
        for (double j = 0; j< NbVertY-1; j++) {
            int row = i * NbVertY;
            int rowAbove = (i+1) * NbVertY;
            SurfaceTriangles3ui[triangleCount] = row + j;
            SurfaceTriangles3ui[triangleCount+1] = rowAbove + j;
            SurfaceTriangles3ui[triangleCount+2] = rowAbove+ j +1;
            
            SurfaceTriangles3ui[triangleCount+3] = rowAbove+ j +1;
            SurfaceTriangles3ui[triangleCount+4] = row + j + 1;
            SurfaceTriangles3ui[triangleCount+5] = row + j;
            
            triangleCount += 6;
        }
    }
    
    
    //recalculate normals
    for (int i = 0; i+2 < SurfaceTriangles3ui.size(); i+=3){
        float vector[3], vector2[3];
        
        float v1[] = { SurfaceVertices3f[ SurfaceTriangles3ui[i] *3 + 0], SurfaceVertices3f[ SurfaceTriangles3ui[i] *3 + 1],  SurfaceVertices3f[ SurfaceTriangles3ui[i] *3 + 2]};
        float v2[] = {SurfaceVertices3f[ SurfaceTriangles3ui[i+1] *3 + 0], SurfaceVertices3f[ SurfaceTriangles3ui[i+1] *3 + 1],  SurfaceVertices3f[ SurfaceTriangles3ui[i+1] *3 + 2]};
        float v3[] = {SurfaceVertices3f[ SurfaceTriangles3ui[i+2] *3 + 0], SurfaceVertices3f[ SurfaceTriangles3ui[i+2] *3 + 1],  SurfaceVertices3f[ SurfaceTriangles3ui[i+2] *3 + 2]};
        //float v4[] = {-1, -1, -1};
        
        vector[0] = v3[0] - v1[0];
        vector[1] = v3[1] - v1[1];
        vector[2] = v3[2] - v1[2];
        
        vector2[0] = v2[0] - v1[0];
        vector2[1] = v2[1] - v1[1];
        vector2[2] = v2[2] - v1[2];
        
        float normal[3];
        CrossProduct(vector2,vector, normal);
        
        updatePointNormal(normal, SurfaceTriangles3ui[i]);
        updatePointNormal(normal, SurfaceTriangles3ui[i+1]);
        updatePointNormal(normal, SurfaceTriangles3ui[i+2]);
    }
}

std::vector<float> Terrain::getVertices(){
    return SurfaceVertices3f;
}

std::vector<float> Terrain::getNormals(){
    return SurfaceNormals3f;
}

std::vector<float> Terrain::getUv(){
    return SurfaceTexCoords2f;
}

std::vector<unsigned int> Terrain::getFaces(){
    return SurfaceTriangles3ui;
}
