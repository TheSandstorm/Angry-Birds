#pragma once
#include "InputManger.h"
#include "Utility.h"
#include "Level.h"
#include "Clock.h"
class Game
{
public:
	void Process();
	Game(int _CurrentLevel);
	~Game();
	void Init(int _Level);
	void Render();

private:
	unsigned int CurrentLevel;
	float DeltaTime;
	Level* mLevel;
};