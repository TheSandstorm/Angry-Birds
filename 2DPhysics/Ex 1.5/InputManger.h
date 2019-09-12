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
	CInputManager();
	static void ProcessKeyInput();
	static void ProcessKeyInput(float _DeltaTime);

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

	//Contains an array of all Special characters on a keyboard
	static unsigned char KeySpecialArray[255];

	//Contains an array of all normal characters on a keyboard
	static unsigned char KeyArray[255];

	//Contains an array of the 3 mouse buttons
	static unsigned int MouseArray[3];
private:

	//Keeps current mouse position
	static glm::vec2 MousePos;

	static void NormKeyDown(unsigned char key, int x, int y);
	static void NormKeyUp(unsigned char key, int x, int y);
	static void SpecialKeyDown(int key, int x, int y);
	static void SpecialKeyUp(int key, int x, int y);

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

