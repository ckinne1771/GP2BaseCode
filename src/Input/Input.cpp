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
	auto iter = m_AttachedJoypads.begin();
	while (iter != m_AttachedJoypads.end())
	{
		if ((*iter))
		{
			delete (*iter);
			iter = m_AttachedJoypads.erase(iter);
		}
		else
			iter++;
	}
	m_AttachedJoypads.clear();
}

void Input::update()
{
}

bool Input::init(const std::string& inputDBFilename)
{
	SDL_GameControllerAddMappingsFromFile(inputDBFilename.c_str());
	int numOfJoypads = SDL_NumJoysticks();
	for (int i = 0; i < numOfJoypads; i++)
	{
		//Is the joypad able to use the new controller interface
		if (SDL_IsGameController(i))
		{
			SDL_GameController *controller = SDL_GameControllerOpen(i);
			Joypad * joypad = new Joypad(controller);
			m_AttachedJoypads.push_back(joypad);
		}
	}

    return true;
}