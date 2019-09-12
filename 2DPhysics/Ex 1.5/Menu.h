#pragma once
#include "TextManager.h"
#include "InputManger.h"
#include "ShaderLoader.h"
#include "Utility.h"

enum SceneState {
	START_MENU,
	OPTION_MENU,
	LEVEL_SELECT,
	LEVEL_1,
	LEVEL_2,
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