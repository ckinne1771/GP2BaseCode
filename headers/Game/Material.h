#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>

#include "Game/Component.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#elif WIN32
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#endif

#include <string>

class Material :public Component
{
public:
	Material();
	~Material();

	void createShaderProgram();
	bool linkShaderProgram(GLuint vertexShader,GLuint fragmentShader);
	void bindProgram();
	void destroy();

	GLint getUniformLocation(const std::string& variableName);
	
private:
	GLint m_ShaderProgram;
};

#endif