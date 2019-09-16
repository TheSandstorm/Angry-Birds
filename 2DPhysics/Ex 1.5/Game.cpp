#include "Game.h"

Game::Game(int _CurrentLevel) 
{ 
	CurrentLevel = _CurrentLevel;
	CClock::GetInstance(); 
	mLevel = new Level;
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
		this->Init();
		//Restart the level
	}
	mLevel->Process(DeltaTime);

}

void Game::Init()
{	
	mLevel->Init(CurrentLevel);
}

void Game::Render()
{
	mLevel->Render();
}
