#pragma once

#include "Object.h"

class Ground : public Object
{
public:
	Ground();
	Ground(Transform _Transform, b2BodyType _bodytype, GLuint _ShaderProgram, GLuint _Texture);
	~Ground();

	void Init(b2World* _World);
	void Process();
	void Render();
protected:
	b2PolygonShape DynamicBox;
};