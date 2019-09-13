#include "ProgramManager.h"
std::shared_ptr<CProgramManager> CProgramManager::SceneManagerPtr;
SceneState CProgramManager::CurrentState;

CProgramManager::CProgramManager()
{
	//For Culling the objects
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	//Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(3.0f);
	//Creating the shaders
	glClearColor(1.0f, 0.6f, 0.0f, 1.0f); //Orange

#pragma region StartMenu
	std::vector<std::string> StartOpt;
	StartOpt.push_back("Start");
	StartOpt.push_back("Options");
	StartOpt.push_back("Quit");

	StartMenu = std::make_shared<CMenu>(StartOpt, glm::vec2(-90.0f, -200.0f));
#pragma endregion

#pragma region LevelSelect
	std::vector<std::string> LevelOpt;
	LevelOpt.push_back("Level 1");
	LevelOpt.push_back("Level 2");
	LevelOpt.push_back("Back");

	LevelSelect = std::make_shared<CMenu>(LevelOpt, glm::vec2(-90.0f, -200.0f));
#pragma endregion

#pragma region OptionsMenu
	std::vector<std::string> OptionsOpt;
	OptionsOpt.push_back("");// Insert changeable text here
	OptionsOpt.push_back("Back");

	OptionMenu = std::make_shared<CMenu>(OptionsOpt, glm::vec2(-90.0f, -200.0f));
#pragma endregion

#pragma region EndGameMenu
	std::vector<std::string> EndOpt;
	EndOpt.push_back("Restart Level");
	EndOpt.push_back("Level Select");
	EndOpt.push_back("Back");

	EndScreen = std::make_shared<CMenu>(EndOpt, glm::vec2(-90.0f, -200.0f));

#pragma endregion
}
CProgramManager::~CProgramManager()
{
	delete IM; 
	IM = nullptr;
	delete Game;
	Game = nullptr;
}

void CProgramManager::DestoryInstance()
{
	SceneManagerPtr = nullptr;
}

std::shared_ptr<CProgramManager> CProgramManager::GetInstance()
{
	if (SceneManagerPtr == nullptr) SceneManagerPtr = std::shared_ptr<CProgramManager>(new CProgramManager());
	return SceneManagerPtr;
}

void CProgramManager::Update()
{
	char Result = IM->ProcessKeys();
	switch (CurrentState)
	{

	case START_MENU:
	{
		int TempOutput = NULL;
		StartMenu->Process(TempOutput);
		CInputManager::ProcessKeyInput();

		switch (TempOutput)
		{
		case 0:
			CurrentState = LEVEL_SELECT;
			break;
		case 1:
			CurrentState = OPTION_MENU;
			break;
		case 2:
			glutLeaveMainLoop();
		default:
			break;
		}

	}
	case LEVEL_SELECT:
	{
		int TempOutput = NULL;
		LevelSelect->Process(TempOutput);
		CInputManager::ProcessKeyInput();

		switch (TempOutput)
		{
		case 0:
			CurrentState = LEVEL_1;
			Game->Init(1);
			//Init Game Level 1
			break;
		case 1:
			Game->Init(2);
			CurrentState = LEVEL_2;
			//Init Game Level 2
			break;
		case 2:
			CurrentState = START_MENU;
			break;
		default:
			break;
		}
	}
	case OPTION_MENU:
	{
		int TempOutput = NULL;
		OptionMenu->Process(TempOutput);
		CInputManager::ProcessKeyInput();

		switch (TempOutput)
		{
		case 0:
			//Any Options we have
			break;
		case 1:
			CurrentState = START_MENU;
			break;
		default:
			break;
		}
	}
	case LEVEL_1:
	case LEVEL_2:
	{
		Game->Process();
		//Process would go here
	}
	case END_MENU:
	{
		int TempOutput = NULL;
		EndScreen->Process(TempOutput);
		CInputManager::ProcessKeyInput();
		switch (TempOutput)
		{
		case 0:
			//Restart Level would go here
			break;
		case 1:
			CurrentState = START_MENU;
			break;
		default:
			break;
		}
	}
	default:
		break;
	}
}

void CProgramManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (CurrentState)
	{
	case START_MENU:
		DrawMenu();
		break;
	case LEVEL_SELECT:
		DrawLevelSelect();
		break;
	case LEVEL_1:
	case LEVEL_2:
		DrawLevel();
		//Switches states
		break;
	case OPTION_MENU:
		DrawOption();
		break;
	case END_MENU:
		DrawEndScreen();
		break;

	default:break;
	}
}

void CProgramManager::DrawMenu()
{
	//Title->Render();
	StartMenu->Render();
}

void CProgramManager::DrawLevelSelect()
{
	LevelSelect->Render();
}

void CProgramManager::DrawOption()
{
	OptionMenu->Render();
}

void CProgramManager::DrawLevel()
{
	Game->Render();
}

void CProgramManager::DrawEndScreen()
{
	EndScreen->Render();
}