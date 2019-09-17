#pragma once
#include "InputManger.h"
#include "Utility.h"
#include "Level.h"
#include "Clock.h"
#include "InputManger.h"
class Game
{
public:
	void Process(CInputManager* _IM);
	Game(int _CurrentLevel);
	~Game();
	void Init();
	void Render();

private:
	unsigned int CurrentLevel;
	float DeltaTime;
	Level* mLevel;
};