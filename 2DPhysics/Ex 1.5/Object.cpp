#include "Object.h"

Object::Object(Transform _transform, b2BodyType _type)
{
	TransformSelf = _transform;
	bType = _type;
}

Object::~Object()
{
	BoxBody->GetWorld()->DestroyBody(BoxBody);
	BoxBody = nullptr;
	delete Data;
	Data = nullptr;
}
