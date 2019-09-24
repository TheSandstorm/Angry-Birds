#pragma once
#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Glass : public Object
{
public:
	Glass();
	~Glass();
	Glass(Transform _Transform, b2BodyType _Type, GLuint _ShaderProgram, GLuint _Texture);

	void Init(b2World * _World);
	bool Process();
	void Render();
protected:
	b2PolygonShape DynamicBox;

};