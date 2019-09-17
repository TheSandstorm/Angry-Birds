#pragma once
#include "Utility.h"
#include "MeshManager.h"
#include <string>

struct ObjectData {
	std::string ObjectType;
	bool IsMarkedForDestruction = false;

	void MarkForDestruction() {
		IsMarkedForDestruction = true;
	}
};

class Object
{
public:
	Object();
	Object(Transform _transform, b2BodyType _type, GLuint _ShaderProgram, GLuint _Texture);
	~Object();

	b2Body* GetBody() { return BoxBody; };
	
	virtual void Init() = 0;
	virtual void Process() = 0;
	virtual void Render() = 0;

	ObjectData* Data;

protected:
	MESH MeshObject;
	//Temp
	GLuint VAO, VBO, EBO;
	GLuint VAO1, VBO1, EBO1;

	GLuint ShaderProgram, Texture;
	Transform TransformSelf;

	b2Body* BoxBody;
	b2BodyType bType;

};

