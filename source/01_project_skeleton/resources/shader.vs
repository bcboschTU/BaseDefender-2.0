#version 330

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 Normal_cameraspaceV;
out vec3 EyeDirection_cameraspace;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform int texid;

void main()
{
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
    Position_worldspace = (M * vec4(vertexPosition_modelspace,1)).xyz;
    
    EyeDirection_cameraspace = - ( V * M * vec4(vertexPosition_modelspace,1)).xyz;
    
    Normal_cameraspace = (M * vec4(vertexNormal_modelspace,0)).xyz;
    Normal_cameraspaceV = ( V * M * vec4(vertexNormal_modelspace,0)).xyz;
    UV = vertexUV;
}