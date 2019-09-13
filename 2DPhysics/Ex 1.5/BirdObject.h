#pragma once
#include "Utility.h"
#include "Object.h"
class Bird : Object
{
public:

	void Render();
private:
	Transform transform;
};