#include "Clock.h"

std::shared_ptr<CClock> CClock::ClockPtr = nullptr;
float CClock::OldTime = 0.0f;

//init
CClock::CClock() {
	OldTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME) / 1000.0f);
};

std::shared_ptr<CClock> CClock::GetInstance()
{
	if (ClockPtr == nullptr) ClockPtr = std::shared_ptr <CClock>(new CClock());
	return ClockPtr;
};
//Does the deltaTime calculation
float CClock::GetDeltaTime() {
	float CurrentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME) / 1000.0f);
	float deltaTime = (CurrentTime - OldTime);
	OldTime = CurrentTime;
	return deltaTime;
};