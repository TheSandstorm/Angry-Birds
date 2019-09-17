#pragma once

#include "Object.h"

class Ground : public Object
{
public:
	Ground();
	Ground(Transform _Transform, b2BodyType _bodytype);
	~Ground();

	void Init();
	void Process();
	void Render();
protected:
	b2PolygonShape DynamicBox;
};