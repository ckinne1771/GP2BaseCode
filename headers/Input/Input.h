//
//  Input.h
//  GP2BaseCode
//
//  Created by Brian on 23/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#ifndef Input_h
#define Input_h

#include "Keyboard.h"
#include "Mouse.h"

class Input
{
public:
    Input();
    ~Input();
    
    bool init();
    
    void update();
    
    Keyboard& getKeyboard()
    {
        return m_Keyboard;
    };
    
    Mouse& getMouse()
    {
        return m_Mouse;
    };
    
private:
    Keyboard m_Keyboard;
    Mouse m_Mouse;
};

static Input InputSystem;
#endif
