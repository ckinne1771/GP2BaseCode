#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2_image/SDL_image.h>
#elif WIN32
#include <SDL_opengl.h>
#include <SDL_image.h>
#endif


#include <iostream>
#include <string>


GLuint loadTextureFromFile(const std::string& filename);

#endif