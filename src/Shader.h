//
//  Shader.h
//  GP2BaseCode
//
//  Created by Brian on 01/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#elif WIN32
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#endif

#include <iostream>
#include <fstream>
#include <string>

enum SHADER_TYPE
{
	VERTEX_SHADER=GL_VERTEX_SHADER,
	GEOMETRY_SHADER=GL_GEOMETRY_SHADER,
	TESSELLATION_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
	TESSELLATION_EVAL_SHADER=GL_TESS_EVALUATION_SHADER,
	FRAGMENT_SHADER=GL_FRAGMENT_SHADER
};

GLuint loadShaderFromFile(const std::string& filename, SHADER_TYPE shaderType);
GLuint loadShaderFromMemory(const char * pMem, SHADER_TYPE shaderType);

GLuint loadTextureFromFile(const std::string& filename);
GLuint loadTextureFromFile(const char * pMem);

bool checkForLinkErrors(GLuint program);
bool checkForCompilerErrors(GLuint shaderProgram);

#endif
