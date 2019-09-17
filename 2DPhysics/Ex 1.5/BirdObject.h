#pragma once
#include "Utility.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object.h"




class Bird : Object
{
public:


	Bird();
	void RenderBird();
	void initBird(b2World* _World);

private:
	Transform transform;

	MeshManager* meshmanage;

};


