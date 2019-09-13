#pragma once

#include "Object.h"

class Ground : public Object
{
public:
	Ground();
	~Ground();

	void Init();
	void Process();
	void Render();
protected:
	b2PolygonShape DynamicBox;
};