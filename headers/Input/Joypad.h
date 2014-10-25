#ifndef JOYPAD_H
#define JOYPAD_H

#include <glm/glm.hpp>
#include <string>

using glm::vec2;

//http://hg.libsdl.org/SDL/file/default/include/SDL_joystick.h
enum DPadStates
{
	CENTRED=0x00,
	UP_PRESSED = 0x01,
	DOWN_PRESSED = 0x04,
	LEFT_PRESSED = 0x03,
	RIGHT_PRESSED=0x02,
	RIGHTUP_PRESSED = (RIGHT_PRESSED | UP_PRESSED),
	RIGHTDOWN_PRESSED = (RIGHT_PRESSED | DOWN_PRESSED),
	LEFTUP_PRESSED = (LEFT_PRESSED | UP_PRESSED),
	LEFTDOWN_PRESSED = (LEFT_PRESSED | DOWN_PRESSED)
};

//This was indetified by manually checking the values via SDL Events
enum ButtonIDs
{
	A_BUTTON=10,
	X_BUTTON=12,
	B_BUTTON=11,
	Y_BUTTON=13,
	BACK_BUTTON=5,
	START_BUTTON=4,
	LEFT_BUMPER_BUTTON=8,
	RIGHT_BUMPER_BUTTON=9,
	LEFT_THUMBSTICK_BUTTON=6,
	RIGHT_THUMBSTICK_BUTTON=7,
};

enum AxisID
{
	LEFT_AXIS = 0,
	RIGHT_AXIS=1,
	LEFT_TRIGGER=2,
	RIGHT_TRIGGER=3,

};

class Joypad
{
public:
	Joypad();
	~Joypad();

	void setName(const std::string& name)
	{
		m_Name = name;
	}
	const std::string& getName()
	{
		return m_Name;
	};

	void setButtonUp(short buttonIndex);
	void setButtonDown(short buttonIndex);
private:
	//This assumes we are using a 360 Joypad
	bool m_ButtonsDown[10];
	bool m_ButtonsUp[10];
	vec2 m_LeftThumbStickAxis;
	vec2 m_RightThumbStickAxis;
	float m_LeftTrigger;
	float m_RightTrigger;
	DPadStates dpadState;
	std::string m_Name;
};

#endif