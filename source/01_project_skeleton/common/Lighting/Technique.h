//
//  Technique.h
//  opengl-series
//
//  Created by Bert Bosch on 24-03-15.
//
//

#ifndef __opengl_series__Technique__
#define __opengl_series__Technique__

#include <list>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Util.h"


class Technique
{
public:
    
    Technique();
    
    virtual ~Technique();
    
    virtual bool Init();
    
    void Enable();
    
protected:
    
    bool AddShader(GLenum ShaderType, const char* pFilename);
    
    bool Finalize();
    
    GLint GetUniformLocation(const char* pUniformName);
    
    GLint GetProgramParam(GLint param);
    
    GLuint m_shaderProg;
    
private:
    
    typedef std::list<GLuint> ShaderObjList;
    ShaderObjList m_shaderObjList;
};

#endif /* defined(__opengl_series__Technique__) */
