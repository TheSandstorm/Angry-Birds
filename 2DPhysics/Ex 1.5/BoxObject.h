#pragma once
#include "Object.h"
//#include <Box2D/Box2D.h>
#include "Dependencies/Box2D/Box2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Box: public Object
{
public:
	Box();
	~Box();
	Box(Transform _Transform, b2BodyType _Type, GLuint _ShaderProgram, GLuint _Texture);

	void Init(b2World * _World);
	void Process();
	void Render();
protected:
	b2PolygonShape DynamicBox;

};