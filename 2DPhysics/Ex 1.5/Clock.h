#pragma once
#include <time.h>
#include <glut.h>
#include <fstream>

class CClock {
public:
	~CClock() {};
	static std::shared_ptr<CClock> GetInstance();
	static void DestroyInstance() { ClockPtr = nullptr; };
	static float GetDeltaTime();
private:
	CClock();
	static std::shared_ptr<CClock> ClockPtr;
	static float OldTime;
};
