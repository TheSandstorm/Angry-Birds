
#include "Menu.h"

CMenu::CMenu() {}

CMenu::~CMenu() 
{
	OptionVect.clear();
};

CMenu::CMenu(std::vector<std::string> _OptVect, glm::vec2 _Pos)
{
	NumMenuOptions = 0;
	CurrentOption = 0;
	glm::vec2 Position = _Pos;

	//Iterating through the provided option vect
	for (unsigned int i = 0; i < _OptVect.size(); ++i)
	{
		OptionVect.push_back(std::make_shared<CTextLabel>(_OptVect[i], SoundnFonts::NormalFontString.data(), Position));
		Position.y -= 60.0f;
	}
	NumMenuOptions = _OptVect.size() - 1;
}

void CMenu::IncrementMenu() 
{
	if (CurrentOption == NumMenuOptions) CurrentOption = 0;
	else ++CurrentOption;
}

void CMenu::DecrementMenu()
{
	if (CurrentOption == 0) CurrentOption = NumMenuOptions;
	else --CurrentOption;
}

void CMenu::Process(int& _Option) {
	if (CInputManager::KeySpecialArray[GLUT_KEY_UP] == FIRST_PRESSED) {
		DecrementMenu();
	}
	else if (CInputManager::KeySpecialArray[GLUT_KEY_DOWN] == FIRST_PRESSED) {
		IncrementMenu();
	}
	else if (CInputManager::KeyArray['\r'] == FIRST_PRESSED) {
		_Option = CurrentOption;
		CurrentOption = 0;
		SelectOption(CurrentOption);
		return;
	}

	SelectOption(CurrentOption);

	_Option = 999;
}

void CMenu::ReplaceOption(int _OptIndex, std::string _OptionText) {
	if (_OptIndex > NumMenuOptions || _OptIndex < 0) return;
	OptionVect[_OptIndex]->SetText(_OptionText);
}

void CMenu::SelectOption(unsigned int _Option) {
	for (unsigned int i = 0; i < OptionVect.size(); ++i) {
		if (i == _Option) {
			OptionVect[i]->SetColor(glm::vec3(0.10f, 0.2f, 0.37f));
			OptionVect[i]->SetScale(0.8f);
		}
		else {
			OptionVect[i]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
			OptionVect[i]->SetScale(0.5f);
		}
	}
}

void CMenu::Render() 
{
	for (auto it : OptionVect) it->Render();
}