#include "Game.h"

Game::Game() {}

Game::~Game() {}

void Game::Process()
{
	if (CInputManager::KeyArray['r'] == FIRST_PRESSED)
	{
		this->Init(CurrentLevel);
		//Restart the level
	}
}

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(int _Level)
{

}

void Game::Render()
{
}
