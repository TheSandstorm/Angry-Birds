#pragma once

#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Ground : public Object
{
public:
	Ground();
	Ground(Transform _Transform, b2BodyType _bodytype, GLuint _ShaderProgram, GLuint _Texture);
	~Ground();

	void Init(b2World* _World);
	bool Process();
	void Render();
protected:
	b2PolygonShape DynamicBox;
};