//
//  Input.cpp
//  GP2BaseCode
//
//  Created by Brian on 23/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#include "Input/Input.h"


Input::Input()
{
    
}

Input::~Input()
{
	
}

void Input::destroy()
{
	auto iter = m_SDLJoypads.begin();
	while (iter != m_SDLJoypads.end())
	{
		if ((*iter))
		{
			SDL_JoystickClose((*iter));
		}
		iter++;
	}
	m_SDLJoypads.clear();
}

void Input::update()
{
}

bool Input::init()
{
	SDL_JoystickEventState(SDL_ENABLE);
	//get Number of joysticks
	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		Joypad pad;
		pad.setName(SDL_JoystickNameForIndex(i));
		m_AttachedJoypads.push_back(pad);
		m_SDLJoypads.push_back(SDL_JoystickOpen(i));
	}
    return true;
}