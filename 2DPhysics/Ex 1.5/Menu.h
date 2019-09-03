#pragma once
#include "TextManager.h"
#include "InputManger.h"
#include "ShaderLoader.h"
#include "Utility.h"

enum SceneState {
	START_MENU,
	DEMO_START,
	OPTION_MENU,
	MULTIPLAYER_MENU,
	HOST_GAME,
	HOST_LOBBY,
	CLIENT_GAME,
	CLIENT_LOBBY,
	END_MENU
};

class CMenu {
public:
	CMenu();
	~CMenu();
	CMenu(std::vector<std::string> _OptVect, glm::vec2 Pos);
	void IncrementMenu();
	void DecrementMenu();
	int GetCurrentOpt() { return CurrentOption; };
	void ReplaceOption(int _OptIndex, std::string _OptionText);
	void SelectOption(unsigned int _Option);
	void Process(int& _Option);
	void Render();

private:
	std::vector<std::shared_ptr<CTextLabel>> OptionVect;

	GLuint TextShader;
	int NumMenuOptions;
	int CurrentOption;
};