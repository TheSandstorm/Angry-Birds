#pragma once
#include "InputManger.h"
#include "Utility.h"
#include "Level.h"
class Game
{
public:
	void Process();
	Game();
	~Game();
	void Init(int _Level);
	void Render();

private:
	unsigned int CurrentLevel;
	Level Level;
};