#pragma once
#include "ShaderLoader.h"
#include "Triangle.h"
#include "Line.h"
#include "Clock.h"
#include "Utility.h"
#include "Menu.h"
//Camera class needed
#include "MeshManager.h"
#include "InputManger.h"

enum SceneState {
	START_MENU,
	OPTION_MENU,
	LEVEL_SELECT,
	LEVEL_1,
	LEVEL_2,
	END_MENU
};

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
	GLuint shaderProgram;
	CInputManager* IM = new CInputManager;
	ShaderLoader* SL = new ShaderLoader;

	std::vector<std::string> StartOpt;
	std::vector<std::string> OptOpt;

	std::shared_ptr<CMenu> StartMenu;
	std::shared_ptr<CMenu> OptionMenu;

	static SceneState CurrentState;


	glm::vec3 CrossProduct(glm::vec3 A, glm::vec3 B);
};