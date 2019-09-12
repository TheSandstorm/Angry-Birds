#pragma once
#include <fstream>
#include <glew.h>
#include <glm.hpp>
#include <glut.h>
#include <SOIL.h>
#include "ShaderLoader.h"
#include "Utility.h"

enum Object_Attributes
{
	//Object Types
	PLANE_OBJECT,
	CIRCLE_OBJECT
	
};
enum Shader_Attributes
{
	//Shader types
	STANDARD_SHADER,
	STANDARD_CUBEMAP_SHADER,
	FOG_SHADER,
	FOG_CUBEMAP_SHADER,
	STENCIL_SHADER
};

struct MESH
{
	GLuint VAO;
	unsigned int IndicesCount;
};

class MeshManager
{
public:
	~MeshManager();
	static std::shared_ptr<MeshManager> GetInstance();
	static void DestroyInstance();

	static std::shared_ptr<MESH> GetMesh(Object_Attributes _ObjectType);

	static GLuint GetShaderProgram(Shader_Attributes _ShaderType);

	static GLuint SetTexture(const char * _Texture);

private:
	MeshManager();

	static std::shared_ptr<MeshManager> ObjectManagerptr;

	static GLuint CubeMapShader;
	static GLuint FogCubeMapShader;
	static GLuint ObjectShader;
	static GLuint FogObjectShader;
	static GLuint StencilShader;

	//Mesh ptrs
	static std::shared_ptr<MESH> PlaneMesh;

};