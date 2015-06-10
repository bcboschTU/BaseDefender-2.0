//
//  LightingTechnique.cpp
//  opengl-series
//
//  Created by Bert Bosch on 24-03-15.
//
//

#include "LightingTechnique.h"


LightingTechnique::LightingTechnique()
{
}

bool LightingTechnique::Init()
{
    if (!Technique::Init()) {
        return false;
    }
    
    if (!AddShader(GL_VERTEX_SHADER, "shader.vs")) {
        return false;
    }
    
    if (!AddShader(GL_FRAGMENT_SHADER, "shader.fs")) {
        return false;
    }
    
    if (!Finalize()) {
        return false;
    }
    
    matrixID = GetUniformLocation("MVP");
    viewMatrixID = GetUniformLocation("V");
    modelMatrixID = GetUniformLocation("M");
    
    m_samplerLocation0 = GetUniformLocation("myTextureSampler0");
    m_samplerLocation1 = GetUniformLocation("myTextureSampler1");
    m_samplerLocation2 = GetUniformLocation("myTextureSampler2");
    m_samplerLocation3 = GetUniformLocation("myTextureSampler3");
    m_samplerLocation4 = GetUniformLocation("myTextureSampler4");
    m_samplerLocation5 = GetUniformLocation("myTextureSampler5");
    m_samplerLocation6 = GetUniformLocation("myTextureSampler6");
    m_samplerLocation7 = GetUniformLocation("myTextureSampler7");
    m_samplerLocation8 = GetUniformLocation("myTextureSampler8");
    m_samplerLocation9 = GetUniformLocation("myTextureSampler9");
    
    texID = GetUniformLocation("texid");
    
    m_dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Base.Color");
    m_dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
    m_dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
    m_dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
    m_matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
    m_matSpecularPowerLocation = GetUniformLocation("gSpecularPower");
    m_numPointLightsLocation = GetUniformLocation("gNumPointLights");
    m_numSpotLightsLocation = GetUniformLocation("gNumSpotLights");
    
    for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(m_pointLightsLocation) ; i++) {
        char Name[128];
        memset(Name, 0, sizeof(Name));
        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.Color", i);
        m_pointLightsLocation[i].Color = GetUniformLocation(Name);
        
        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.AmbientIntensity", i);
        m_pointLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);
        
        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Position", i);
        m_pointLightsLocation[i].Position = GetUniformLocation(Name);
        
        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.DiffuseIntensity", i);
        m_pointLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);
        
        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Constant", i);
        m_pointLightsLocation[i].Atten.Constant = GetUniformLocation(Name);
        
        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Linear", i);
        m_pointLightsLocation[i].Atten.Linear = GetUniformLocation(Name);
        
        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Exp", i);
        m_pointLightsLocation[i].Atten.Exp = GetUniformLocation(Name);
        
        if (m_pointLightsLocation[i].Color == INVALID_UNIFORM_LOCATION ||
            m_pointLightsLocation[i].AmbientIntensity == INVALID_UNIFORM_LOCATION ||
            m_pointLightsLocation[i].Position == INVALID_UNIFORM_LOCATION ||
            m_pointLightsLocation[i].DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
            m_pointLightsLocation[i].Atten.Constant == INVALID_UNIFORM_LOCATION ||
            m_pointLightsLocation[i].Atten.Linear == INVALID_UNIFORM_LOCATION ||
            m_pointLightsLocation[i].Atten.Exp == INVALID_UNIFORM_LOCATION) {
            return false;
        }
    }
    
    for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(m_spotLightsLocation) ; i++) {
        char Name[128];
        memset(Name, 0, sizeof(Name));
        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.Color", i);
        m_spotLightsLocation[i].Color = GetUniformLocation(Name);
        
        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.AmbientIntensity", i);
        m_spotLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);
        
        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Position", i);
        m_spotLightsLocation[i].Position = GetUniformLocation(Name);
        
        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Direction", i);
        m_spotLightsLocation[i].Direction = GetUniformLocation(Name);
        
        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Cutoff", i);
        m_spotLightsLocation[i].Cutoff = GetUniformLocation(Name);
        
        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.DiffuseIntensity", i);
        m_spotLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);
        
        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Constant", i);
        m_spotLightsLocation[i].Atten.Constant = GetUniformLocation(Name);
        
        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Linear", i);
        m_spotLightsLocation[i].Atten.Linear = GetUniformLocation(Name);
        
        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Exp", i);
        m_spotLightsLocation[i].Atten.Exp = GetUniformLocation(Name);
        
        if (m_spotLightsLocation[i].Color == INVALID_UNIFORM_LOCATION ||
            m_spotLightsLocation[i].AmbientIntensity == INVALID_UNIFORM_LOCATION ||
            m_spotLightsLocation[i].Position == INVALID_UNIFORM_LOCATION ||
            m_spotLightsLocation[i].Direction == INVALID_UNIFORM_LOCATION ||
            m_spotLightsLocation[i].Cutoff == INVALID_UNIFORM_LOCATION ||
            m_spotLightsLocation[i].DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
            m_spotLightsLocation[i].Atten.Constant == INVALID_UNIFORM_LOCATION ||
            m_spotLightsLocation[i].Atten.Linear == INVALID_UNIFORM_LOCATION ||
            m_spotLightsLocation[i].Atten.Exp == INVALID_UNIFORM_LOCATION) {
            return false;
        }
    }
    
    if (m_dirLightLocation.AmbientIntensity == INVALID_UNIFORM_LOCATION ||
        matrixID == INVALID_UNIFORM_LOCATION ||
        viewMatrixID == INVALID_UNIFORM_LOCATION ||
        modelMatrixID == INVALID_UNIFORM_LOCATION ||
        m_samplerLocation0 == INVALID_UNIFORM_LOCATION ||
        m_samplerLocation1 == INVALID_UNIFORM_LOCATION ||
        m_samplerLocation2 == INVALID_UNIFORM_LOCATION ||
        m_dirLightLocation.Color == INVALID_UNIFORM_LOCATION ||
        m_dirLightLocation.DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
        m_dirLightLocation.Direction == INVALID_UNIFORM_LOCATION ||
        m_matSpecularIntensityLocation == INVALID_UNIFORM_LOCATION ||
        m_matSpecularPowerLocation == INVALID_UNIFORM_LOCATION ||
        m_numPointLightsLocation == INVALID_UNIFORM_LOCATION||
        m_numSpotLightsLocation == INVALID_UNIFORM_LOCATION) {
        return false;
    }
    
    return true;
}

void LightingTechnique::SetMatrix(const glm::mat4& MVP)
{
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
}


void LightingTechnique::SetViewMatrix(const glm::mat4& ViewMatrix)
{
    glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
}

void LightingTechnique::SetModeldMatrix(const glm::mat4& ModelMatrix)
{
    glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
}

void LightingTechnique::SetTextId(int i){
    glUniform1i(texID, i);
}


void LightingTechnique::SetTextureUnit(unsigned int TextureUnit)
{
    //if(TextureUnit == 0)
    //    glActiveTexture(GL_TEXTURE0);
    //if(TextureUnit == 1)
    //    glActiveTexture(GL_TEXTURE1);
    //glActiveTexture(GL_TEXTURE0 + TextureUnit);
    //glUniform1i(m_samplerLocation0, TextureUnit);
}


void LightingTechnique::SetDirectionalLight(const DirectionalLight& Light)
{
    glUniform3f(m_dirLightLocation.Color, Light.Color.x, Light.Color.y, Light.Color.z);
    glUniform1f(m_dirLightLocation.AmbientIntensity, Light.AmbientIntensity);
    glm::vec3 Direction = Light.Direction;
    Direction = glm::normalize(Direction);
    glUniform3f(m_dirLightLocation.Direction, Direction.x, Direction.y, Direction.z);
    glUniform1f(m_dirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
}

void LightingTechnique::SetMatSpecularIntensity(float Intensity)
{
    glUniform1f(m_matSpecularIntensityLocation, Intensity);
}

void LightingTechnique::SetMatSpecularPower(float Power)
{
    glUniform1f(m_matSpecularPowerLocation, Power);
}

void LightingTechnique::addTexture(GLuint texture, unsigned int index){
    if(index == 0){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(m_samplerLocation0, 0);
    }
    if(index == 1){
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(m_samplerLocation1, 1);
    }
    if(index == 2){
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(m_samplerLocation2, 2);
    }
    if(index == 3){
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(m_samplerLocation2, 3);
    }
    if(index == 4){
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(m_samplerLocation2, 4);
    }
    if(index == 5){
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(m_samplerLocation2, 5);
    }
    if(index == 6){
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(m_samplerLocation2, 6);
    }
    if(index == 7){
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(m_samplerLocation2, 7);
    }
    if(index == 8){
        glActiveTexture(GL_TEXTURE8);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(m_samplerLocation2, 8);
    }
    if(index == 9){
        glActiveTexture(GL_TEXTURE9);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(m_samplerLocation2, 9);
    }
    
    
}

void LightingTechnique::SetPointLights(unsigned int NumLights, const PointLight* pLights)
{
    glUniform1i(m_numPointLightsLocation, NumLights);
    
    for (unsigned int i = 0 ; i < NumLights ; i++) {
        glUniform3f(m_pointLightsLocation[i].Color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
        glUniform1f(m_pointLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
        glUniform1f(m_pointLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
        glUniform3f(m_pointLightsLocation[i].Position, pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
        glUniform1f(m_pointLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
        glUniform1f(m_pointLightsLocation[i].Atten.Linear, pLights[i].Attenuation.Linear);
        glUniform1f(m_pointLightsLocation[i].Atten.Exp, pLights[i].Attenuation.Exp);
    }
}

void LightingTechnique::SetSpotLights(unsigned int NumLights, const SpotLight* pLights)
{
    glUniform1i(m_numSpotLightsLocation, NumLights);
    
    for (unsigned int i = 0 ; i < NumLights ; i++) {
        glUniform3f(m_spotLightsLocation[i].Color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
        glUniform1f(m_spotLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
        glUniform1f(m_spotLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
        glUniform3f(m_spotLightsLocation[i].Position,  pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
        glm::vec3 Direction = pLights[i].Direction;
        Direction = glm::normalize(Direction);
        glUniform3f(m_spotLightsLocation[i].Direction, Direction.x, Direction.y, Direction.z);
        float rot = pLights[i].Cutoff * (M_PI/180);
        glUniform1f(m_spotLightsLocation[i].Cutoff, cosf(rot));
        glUniform1f(m_spotLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
        glUniform1f(m_spotLightsLocation[i].Atten.Linear,   pLights[i].Attenuation.Linear);
        glUniform1f(m_spotLightsLocation[i].Atten.Exp,      pLights[i].Attenuation.Exp);
    }
}