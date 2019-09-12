#include "InputManger.h"
unsigned char CInputManager::KeyArray[255];
unsigned char CInputManager::KeySpecialArray[255];
unsigned int CInputManager::MouseArray[3];
glm::vec2 CInputManager::MousePos = glm::vec2();

CInputManager::CInputManager() {
	for (int i = 0; i < 255; ++i) {
		KeyArray[i] = RELEASED;
		KeySpecialArray[i] = RELEASED;
	}
	for (int i = 0; i < 3; ++i) MouseArray[i] = RELEASED;
}
//Main input
void CInputManager::ProcessKeyInput(float _DeltaTime)
{

}

//Menu input
void CInputManager::ProcessKeyInput() {
	glutSpecialFunc(CInputManager::SpecialKeyDown);
	glutSpecialUpFunc(CInputManager::SpecialKeyUp);
	glutKeyboardFunc(CInputManager::NormKeyDown);
	glutKeyboardUpFunc(CInputManager::NormKeyUp);

	//UP KEY INPUT
	if (KeySpecialArray[GLUT_KEY_UP] == HELD) {
		//Held Stuff
	}
	else if (KeySpecialArray[GLUT_KEY_UP] == FIRST_PRESSED) {
		KeySpecialArray[GLUT_KEY_UP] = HELD;
	}

	//DOWN KEY INPUT
	else if (KeySpecialArray[GLUT_KEY_DOWN] == HELD) {
		//Held Stuff
	}
	else if (KeySpecialArray[GLUT_KEY_DOWN] == FIRST_PRESSED) {
		KeySpecialArray[GLUT_KEY_DOWN] = HELD;
	}

	//ENTER KEY INPUT
	if (KeyArray['\r'] == HELD) {

	}
	else if (KeyArray['\r'] == FIRST_PRESSED) {
		KeyArray['\r'] = HELD;
	}
}

void CInputManager::NormKeyDown(unsigned char key, int x, int y) {
	KeyArray[key] = FIRST_PRESSED;
}

void CInputManager::NormKeyUp(unsigned char key, int x, int y) {
	KeyArray[key] = RELEASED;
}

void CInputManager::SpecialKeyDown(int key, int x, int y) {
	KeySpecialArray[key] = FIRST_PRESSED;
}

void CInputManager::SpecialKeyUp(int key, int x, int y) {
	KeySpecialArray[key] = RELEASED;
}