#pragma once
#include <glew.h>
#include <freeglut.h>
#include <glm.hpp>
#include "Dependencies\glm\gtx\string_cast.hpp"
#include <iostream>

enum KEYSTATE 
{
	FIRST_PRESSED,
	HELD,
	RELEASED
};

enum MOUSE_INPUT
{
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE
};

class CInputManager 
{
public:

	//Initializes the keys to be in the released state.
	CInputManager()
	{
		for (int i = 0; i < 255; ++i) KeyArray[i] = RELEASED;
		for (int i = 0; i < 3; ++i) MouseArray[i] = RELEASED;
	}

	glm::vec2 GetMousePos() { return MousePos; }

	unsigned char ProcessKeys()
	{
		glutKeyboardFunc(CInputManager::NormKeyDown);
		glutKeyboardUpFunc(CInputManager::NormKeyUp);
		if (KeyArray['t'] == FIRST_PRESSED)
		{
			KeyArray['t'] = HELD;
			return 't';
		}
		if (KeyArray['l'] == FIRST_PRESSED)
		{
			KeyArray['l'] = HELD;
			return 'l';
		}
		else return 'm';
	}

	bool ProcessMouse()
	{
		glutMouseFunc(MouseButton);
		if (MouseArray[MOUSE_LEFT] == FIRST_PRESSED)
		{
			MouseArray[MOUSE_LEFT] = HELD;
			return true;
		}
		else return false;
	}

private:
	//Contains an array of all normal characters on a keyboard
	static unsigned char KeyArray[255];

	//Contains an array of the 3 mouse buttons
	static unsigned int MouseArray[3];

	//Keeps current mouse position
	static glm::vec2 MousePos;

	static void NormKeyDown(unsigned char key, int x, int y)
	{
		KeyArray[key] = FIRST_PRESSED;
	};

	static void NormKeyUp(unsigned char key, int x, int y) 
	{
		KeyArray[key] = RELEASED;
	};

	static void MouseButton(int button, int state, int x, int y) 
	{	
		if (button < 3) {
			if (state == GLUT_DOWN)
			{
				std::cout << x << "\n" << y << std::endl;
				MouseArray[button] = FIRST_PRESSED;
				MousePos = glm::vec2(x, y);				
			}
			else if (state == GLUT_UP) MouseArray[button] = RELEASED;
		}
	}
};

