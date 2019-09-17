#pragma once
#include "Utility.h"
#include "Object.h"




class Bird : Object
{
public:

	void Render();
	void initBird(b2World* _World);

private:
	Transform transform;

};


