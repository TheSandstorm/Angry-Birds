#pragma once
#include "Utility.h"
#include <Box2D/Box2D.h>

class Level
{
public:
	Level();
	~Level();

private:
	b2Vec2 SlingShotPos;
	std::vector<std::shared_ptr<Entity>> EntityVect;
};
