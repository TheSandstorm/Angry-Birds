#pragma once
#include "BoxObject.h"

class Glass : public Box
{
	Glass();
	~Glass();
	Glass(Transform _transform, b2BodyType _Type);

	void Init();
	bool Process();
	void Render();

};