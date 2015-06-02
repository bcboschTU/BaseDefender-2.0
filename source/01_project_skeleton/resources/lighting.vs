#version 330 core

#define MAX_LIGHTS 1

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
//out vec3 lightDir_cameraspace;
//out vec3 lightDir_cameraspace[MAX_LIGHTS];

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
//uniform vec3 lightPos;
//lightDir is eigenlijk de positie. dus hoeft niet door gegeven te worden eigenlijk.
//kan meteen fragmentshader in
//uniform vec3 lightDir[MAX_LIGHTS];
//uniform float num_lights;
void main(){
    
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
    Position_worldspace = (M * vec4(vertexPosition_modelspace,1)).xyz;
    
    EyeDirection_cameraspace = -( V * M * vec4(vertexPosition_modelspace,1)).xyz;
    
    //lightDir_cameraspace = ( V * vec4(lightPos,1)).xyz + EyeDirection_cameraspace;
    /*
     int i;
    for (i = 0; i< num_lights; i++) {
        lightDir_cameraspace[i] = ( V * vec4(lightDir[i],1)).xyz + EyeDirection_cameraspace;
    }
     */
    Normal_cameraspace = ( V * M * vec4(vertexNormal_modelspace,0)).xyz;
    UV = vertexUV;
}

