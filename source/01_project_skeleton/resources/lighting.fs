#version 330 core

#define MAX_LIGHTS 1

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
//in vec3 lightDir_cameraspace;
//in vec3 lightDir_cameraspace[MAX_LIGHTS];

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform mat4 V;
uniform vec3 lightPos;
//uniform vec3 lightDir[MAX_LIGHTS];
//uniform float num_lights;


void main(){
    vec3 LightColor = vec3(1,1,1);
    float LightPower = 10.0f;
    
    vec3 MaterialDiffuseColor = texture( myTextureSampler, UV ).rgb;
    vec3 MaterialAmbientColor = vec3(0.2, 0.2, 0.2) * MaterialDiffuseColor;
    vec3 MaterialSpecularColor = vec3(0.73, 0.73, 0.73);
    
    
    vec3 colortemp = vec3(0.0,0.0,0.0);
    vec3 n;
    vec3 l;
    vec3 E;
    vec3 R;
    int i;
    float distance = length( lightPos - Position_worldspace );
    //vec3 LightDirection = Position_worldspace - lightDir;
    vec3 lightDircameraspace = ( V * vec4(lightPos,1)).xyz + EyeDirection_cameraspace;
    n = normalize( Normal_cameraspace );
    //l = normalize( lightDir_cameraspace );
    l = normalize( lightDircameraspace );
    float cosTheta = clamp( dot( n,l ), 0,1 );
    //float cosTheta = max(dot(n, l), 0.0)
    
    E = normalize(EyeDirection_cameraspace);
    R = reflect(-l,n);
    float cosAlpha = clamp( dot( E,R ), 0,1 );
    
    color= MaterialAmbientColor +
    MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
    MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,16) / (distance*distance);
    /*
    for (i = 0; i< num_lights; i++) {
        float distance = length( lightDir[i] - Position_worldspace );
        
        n = normalize( Normal_cameraspace );
        l = normalize( lightDir_cameraspace[i] );
        float cosTheta = clamp( dot( n,l ), 0,1 );
        //float cosTheta = max(dot(n, l), 0.0)
        
        E = normalize(EyeDirection_cameraspace);
        R = reflect(-l,n);
        float cosAlpha = clamp( dot( E,R ), 0,1 );
        
        colortemp +=
        MaterialAmbientColor +
        MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
        MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,32) / (distance*distance);
        
    }
    color = colortemp;
     */
    
}