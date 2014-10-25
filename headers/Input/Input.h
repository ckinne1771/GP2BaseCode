//
//  Input.h
//  GP2BaseCode
//
//  Created by Brian on 23/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#ifndef Input_h
#define Input_h

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif WIN32
#include <SDL.h>
#endif

#include "Keyboard.h"
#include "Mouse.h"
#include "Joypad.h"

#include <vector>

class Input
{
public:
    Input();
    ~Input();
    
    bool init();
	void destroy();
    
    void update();
    
    Keyboard& getKeyboard()
    {
        return m_Keyboard;
    };
    
    Mouse& getMouse()
    {
        return m_Mouse;
    };
    
	int getNumberofAttachedJoypads()
	{
		return m_AttachedJoypads.size();
	};

private:
    Keyboard m_Keyboard;
    Mouse m_Mouse;
	std::vector<Joypad> m_AttachedJoypads;
	std::vector<SDL_Joystick*> m_SDLJoypads;
};

static Input InputSystem;

#endif
