//
//  LightingTechnique.h
//  opengl-series
//
//  Created by Bert Bosch on 24-03-15.
//
//

#ifndef __opengl_series__LightingTechnique__
#define __opengl_series__LightingTechnique__

#include <stdio.h>
#include "Technique.h"

struct BaseLight
{
    glm::vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
    
    BaseLight()
    {
        Color = glm::vec3(0.0f, 0.0f, 0.0f);
        AmbientIntensity = 0.0f;
        DiffuseIntensity = 0.0f;
    }
};

struct DirectionalLight : public BaseLight
{
    glm::vec3 Direction;
    
    DirectionalLight()
    {
        Direction = glm::vec3(0.0f, 0.0f, 0.0f);
    }
};

struct PointLight : public BaseLight
{
    glm::vec3 Position;
    
    struct
    {
        float Constant;
        float Linear;
        float Exp;
    } Attenuation;
    
    PointLight()
    {
        Position = glm::vec3(0.0f, 0.0f, 0.0f);
        Attenuation.Constant = 1.0f;
        Attenuation.Linear = 0.0f;
        Attenuation.Exp = 0.0f;
    }
};

struct SpotLight : public PointLight
{
    glm::vec3 Direction;
    float Cutoff;
    
    SpotLight()
    {
        Direction = glm::vec3(0.0f, 0.0f, 0.0f);
        Cutoff = 0.0f;
    }
};

class LightingTechnique : public Technique {
public:
    
    static const unsigned int MAX_POINT_LIGHTS = 20;
    static const unsigned int MAX_SPOT_LIGHTS = 20;
    
    LightingTechnique();
    
    virtual bool Init();
    
    void SetMatrix(const glm::mat4& MVP);
    void SetViewMatrix(const glm::mat4& ViewMatrix);
    void SetModeldMatrix(const glm::mat4& ModelMatrix);
    
    void SetTextureUnit(unsigned int TextureUnit);
    void SetDirectionalLight(const DirectionalLight& Light);
    void SetPointLights(unsigned int NumLights, const PointLight* pLights);
    void SetSpotLights(unsigned int NumLights, const SpotLight* pLights);
    void SetMatSpecularIntensity(float Intensity);
    void SetMatSpecularPower(float Power);
    
private:
    
    GLuint matrixID;
    GLuint viewMatrixID;
    GLuint modelMatrixID;
    GLuint m_samplerLocation;
    GLuint m_eyeWorldPosLocation;
    GLuint m_matSpecularIntensityLocation;
    GLuint m_matSpecularPowerLocation;
    GLuint m_numPointLightsLocation;
    GLuint m_numSpotLightsLocation;
    
    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Direction;
    } m_dirLightLocation;
    
    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        struct
        {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } m_pointLightsLocation[MAX_POINT_LIGHTS];
    
    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        GLuint Direction;
        GLuint Cutoff;
        struct {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } m_spotLightsLocation[MAX_SPOT_LIGHTS];
};

#endif /* defined(__opengl_series__LightingTechnique__) */
