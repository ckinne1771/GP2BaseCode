//
//  Material.h
//  GP2BaseCode
//
//  Created by Brian on 31/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#ifndef Material_h
#define Material_h

#include <GL/glew.h>
#include <string>

#ifdef __APPLE__
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>
#elif WIN32
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#endif

#include "Component.h"

class Material:public Component{
public:
    Material();
    ~Material();
    
    void destroy();
    
    void bind();
    
    bool loadShader(const std::string& vsFilename,const std::string& fsFilename);
    GLint getUniformLocation(const std::string& name);
protected:
private:
    GLuint m_ShaderProgram;
};

#endif
