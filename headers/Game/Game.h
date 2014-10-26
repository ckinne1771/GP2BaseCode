//
//  Game.h
//  GP2BaseCode
//
//  Created by Brian on 21/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>
//maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;


#include <glm/gtc/type_ptr.hpp>

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#elif WIN32
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <gl/GLU.h>
#endif

#include "Input/Input.h"
#include "Utils/Timer.h"

#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "../assets/";
const std::string SHADER_PATH = "shaders/";
const std::string TEXTURE_PATH = "textures/";
const std::string FONT_PATH = "fonts/";
#elif __APPLE__
const std::string ASSET_PATH;
const std::string SHADER_PATH;
const std::string TEXTURE_PATH;
const std::string FONT_PATH;
#else
const std::string ASSET_PATH="/assets/";
const std::string SHADER_PATH="shaders/";
#endif

class GameObject;

class GameApplication
{
public:
    GameApplication();
    virtual ~GameApplication();
    
    virtual bool init(int argc, char * arg[]);
    virtual void update();
    virtual void render();
    virtual void destroy();
	virtual void createGame();
    
    bool isRunning()
    {
        return m_isRunning;
    }
private:
    bool initWindow(const std::string& title,int width, int height,bool fullscreen);
    bool initGraphics();
    bool initInput();
    bool initAudio();
    
    //Messages we are interested in
    void HandleMessages();
    void OnClose();
    void onResizeWindow(int newWidth,int height);
    
protected:
    //Function to set/reset viewport
    void setViewport( int width, int height );
	std::vector<GameObject*> m_SceneGraph;
private:
    SDL_Window * m_pWindow;
    //May shift this out to a renderer!
    SDL_GLContext m_GLContext;
    bool m_isRunning;
    std::string m_GameTitle;
    int m_WindowWidth;
    int m_WindowHeight;
    bool m_WindowFullscreen;
};

#endif
