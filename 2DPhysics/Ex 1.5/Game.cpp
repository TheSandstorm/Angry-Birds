#include "Game.h"

Game::Game(int _CurrentLevel) 
{ 
	CurrentLevel = _CurrentLevel;
	CClock::GetInstance(); 
}

Game::~Game() 
{
	CClock::DestroyInstance();
	delete mLevel;
	mLevel = nullptr;
}

void Game::Process()
{
	DeltaTime = CClock::GetDeltaTime();
	//Could Add a pause menu around here
	if (CInputManager::KeyArray['r'] == FIRST_PRESSED)
	{
		this->Init(CurrentLevel);
		//Restart the level
	}
	mLevel->Process(DeltaTime);

}

void Game::Init(int _Level)
{
	mLevel->Init(_Level);
}

void Game::Render()
{
	mLevel->Render();
}
