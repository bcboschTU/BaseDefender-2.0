#version 330

const int MAX_POINT_LIGHTS = 20;
const int MAX_SPOT_LIGHTS = 20;

in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 Normal_cameraspaceV;
in vec3 EyeDirection_cameraspace;

out vec4 FragColor;

struct BaseLight
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
};

struct DirectionalLight
{
    BaseLight Base;
    vec3 Direction;
};

struct Attenuation
{
    float Constant;
    float Linear;
    float Exp;
};

struct PointLight
{
    BaseLight Base;
    vec3 Position;
    Attenuation Atten;
};

struct SpotLight
{
    PointLight Base;
    vec3 Direction;
    float Cutoff;
};

//lights
uniform int gNumPointLights;
uniform int gNumSpotLights;
uniform DirectionalLight gDirectionalLight;
uniform PointLight gPointLights[MAX_POINT_LIGHTS];
uniform SpotLight gSpotLights[MAX_SPOT_LIGHTS];

//specular values
uniform float gMatSpecularIntensity;
uniform float gSpecularPower;
//texture
uniform sampler2D myTextureSampler0;
uniform sampler2D myTextureSampler1;
uniform sampler2D myTextureSampler2;
uniform sampler2D myTextureSampler3;
uniform sampler2D myTextureSampler4;
uniform sampler2D myTextureSampler5;
uniform sampler2D myTextureSampler6;
uniform sampler2D myTextureSampler7;
uniform sampler2D myTextureSampler8;
uniform sampler2D myTextureSampler9;

//matrixes
uniform mat4 V;
uniform int texid;

vec4 CalcLightInternal(BaseLight Light, vec3 l, vec3 n)
{
    vec4 AmbientColor = vec4(Light.Color, 1.0f) * Light.AmbientIntensity;
    
    float DiffuseFactor = clamp( dot( n,l ), 0,1 );
    
    vec4 DiffuseColor  = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);
    
    if (DiffuseFactor > 0) {
        //diffuse
        DiffuseColor = vec4(Light.Color, 1.0f) * Light.DiffuseIntensity * DiffuseFactor;
        
        
        //specular
        vec3 E = normalize(EyeDirection_cameraspace);
        vec3 R = normalize(reflect(-l, n));
        float SpecularFactor = clamp(dot(E,R),0,1);

        SpecularFactor = pow(SpecularFactor, gSpecularPower);
        if (SpecularFactor > 0) {
            SpecularColor = vec4(Light.Color, 1.0f) *
            gMatSpecularIntensity * SpecularFactor;
        }
    }
    
    return (AmbientColor + DiffuseColor + SpecularColor);
}


vec4 CalcDirectionalLight(vec3 n)
{
    return CalcLightInternal(gDirectionalLight.Base, gDirectionalLight.Direction, n);
}

vec4 CalcPointLight(PointLight light, vec3 n)
{
    float distance = length(light.Position - Position_worldspace);
    
    vec3 lightDircameraspace = ( V * vec4(light.Position,1)).xyz + EyeDirection_cameraspace;
    
    vec3 l = normalize(lightDircameraspace);
    
    vec4 Color = CalcLightInternal(light.Base, l, n);
    
    float atten =  light.Atten.Constant + light.Atten.Linear * distance + light.Atten.Exp * distance * distance;
    
    return Color/atten;
}

vec4 CalcSpotLight(SpotLight l, vec3 n)
{
    vec3 LightToPixel = normalize(Position_worldspace - l.Base.Position);
    
    
    float SpotFactor = dot(LightToPixel, l.Direction);
    
    if (SpotFactor > l.Cutoff) {
        vec4 Color = CalcPointLight(l.Base, n);
        return Color * (1.0 - (1.0 - SpotFactor) * 1.0/(1.0 - l.Cutoff));
    }
    else {
        return vec4(0,0,0,0);
    }
}

void main()
{
    vec3 n = normalize(Normal_cameraspace);
    vec3 n2 = normalize(Normal_cameraspaceV);
    vec4 TotalLight = CalcDirectionalLight(n);
    
    for (int i = 0 ; i < gNumPointLights ; i++) {
        TotalLight += CalcPointLight(gPointLights[i], n2);
    }
    
    for (int i = 0 ; i < gNumSpotLights ; i++) {
        TotalLight += CalcSpotLight(gSpotLights[i], n2);
    }
    
    if(texid == 0){
        FragColor = texture(myTextureSampler0, UV) * TotalLight;
    }
    else if(texid == 1){
        FragColor = texture(myTextureSampler1, UV) * TotalLight;
    }
    else if(texid == 2){
        FragColor = texture(myTextureSampler2, UV) * TotalLight;
    }
    else if(texid == 3){
        FragColor = texture(myTextureSampler3, UV) * TotalLight;
    }
    else if(texid == 4){
        FragColor = texture(myTextureSampler4, UV) * TotalLight;
    }
    else if(texid == 5){
        FragColor = texture(myTextureSampler5, UV) * TotalLight;
    }
    else if(texid == 6){
        FragColor = texture(myTextureSampler6, UV) * TotalLight;
    }
    else if(texid == 7){
        FragColor = texture(myTextureSampler7, UV) * TotalLight;
    }
    else if(texid == 8){
        FragColor = texture(myTextureSampler8, UV) * TotalLight;
    }
    else if(texid == 9){
        FragColor = texture(myTextureSampler9, UV) * TotalLight;
    }
}
