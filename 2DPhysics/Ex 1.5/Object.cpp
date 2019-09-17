#include "Object.h"

Object::Object()
{
}

Object::Object(Transform _transform, b2BodyType _type, GLuint _ShaderProgram, GLuint _Texture)
{
	TransformSelf = _transform;
	bType = _type;
	ShaderProgram = _ShaderProgram;
	Texture = _Texture;
}

Object::~Object()
{
	BoxBody->GetWorld()->DestroyBody(BoxBody);
}
