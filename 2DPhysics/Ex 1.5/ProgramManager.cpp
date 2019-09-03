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
	shaderProgram = SL->CreateProgram(
		const_cast<char*>("Resources/Shaders/Vertex Shader.vs"),
		const_cast<char*>("Resources/Shaders/Fragment Shader.fs")
	);
	glClearColor(1.0f, 0.6f, 0.0f, 1.0f); //Orange

#pragma region StartMenu
	std::vector<std::string> StartOpt;
	StartOpt.push_back("Start");
	StartOpt.push_back("Options");
	StartOpt.push_back("Restart");
	StartOpt.push_back("Quit");

	StartMenu = std::make_shared<CMenu>(StartOpt, glm::vec2(-90.0f, -200.0f));
#pragma endregion
}
CProgramManager::~CProgramManager()
{
	delete IM; IM = nullptr;
	delete SL; SL = nullptr;
	shaderProgram = 0;
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
			break;
		case 1:
			CurrentState = LEVEL_2;
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
	{
		//Level init and then process would go here
	}
	case LEVEL_2:
	{
		//Level init and then process would go here
	}
	case END_MENU:
	{
		int TempOutput = NULL;
		EndMenu->Process(TempOutput);
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
}

glm::vec3 CProgramManager::CrossProduct(glm::vec3 A, glm::vec3 B)
{
	return glm::vec3((A.y*B.z - A.z * B.y), (A.z*B.x - A.x * B.z), (A.x*B.y - A.y * B.x));
}
