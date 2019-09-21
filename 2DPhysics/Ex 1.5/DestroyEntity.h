#pragma once
#include "Level.h"

class DestroyAllTheThings{


public:

	void destroyTheThings(b2Body* bodyToDestroy);

private:
	Level* level;

};
