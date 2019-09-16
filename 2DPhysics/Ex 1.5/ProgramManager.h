#pragma once
#include "ShaderLoader.h"
#include "Triangle.h"
#include "Line.h"
#include "Clock.h"
#include "Utility.h"
#include "Menu.h"
#include "Game.h"
//Camera class needed
#include "MeshManager.h"
#include "InputManger.h"

class CProgramManager
{
public:
	~CProgramManager();
	static void DestoryInstance();
	static std::shared_ptr<CProgramManager> GetInstance();

	static SceneState& GetState() { return CurrentState; };

	void Update();

	void Render();	

private:
	CProgramManager();
	static std::shared_ptr<CProgramManager> SceneManagerPtr;
	CInputManager* IM = new CInputManager;
	Game* newGame;

	std::vector<std::string> StartOpt;
	std::vector<std::string> OptOpt;

	std::shared_ptr<CTextLabel> Title;
	std::shared_ptr<CMenu> StartMenu;
	std::shared_ptr<CMenu> OptionMenu;
	std::shared_ptr<CMenu> LevelSelect;
	std::shared_ptr<CMenu> EndScreen;

	static SceneState CurrentState;

	void DrawMenu();
	void DrawLevelSelect();
	void DrawOption();
	void DrawLevel();
	void DrawEndScreen();

	bool IsGameStart;
};