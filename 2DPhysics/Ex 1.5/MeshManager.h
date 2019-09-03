#pragma once
#include <fstream>
#include <glew.h>
#include <glm.hpp>
#include <glut.h>
#include <SOIL.h>
#include "ShaderLoader.h"
#include "Utility.h"
#include "Model.h"

enum Object_Attributes
{
	//Object Types
	CUBE_OBJECT,
	SPHERE_OBJECT,
	PLANE_OBJECT,
	QUAD_TESS_OBJECT,
	MODEL_PLAYER
	
};
enum Shader_Attributes
{
	//Shader types
	STANDARD_SHADER,
	STANDARD_MODEL_SHADER,
	STANDARD_CUBEMAP_SHADER,
	FOG_SHADER,
	FOG_MODEL_SHADER,
	FOG_CUBEMAP_SHADER,
	STENCIL_SHADER,
	GEOMETRY_SHADER,
	TESS_QUAD_SHADER,
	TESS_TRI_SHADER
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
	static std::shared_ptr<Model> GetModel(Object_Attributes _ObjectType);

	static GLuint GetShaderProgram(Shader_Attributes _ShaderType);

	static GLuint SetTexture(const char * _Texture);

private:
	MeshManager();

	static std::shared_ptr<MeshManager> ObjectManagerptr;

	static GLuint CubeMapShader;
	static GLuint FogCubeMapShader;
	static GLuint ObjectShader;
	static GLuint ModelShader;
	static GLuint TextShader;
	static GLuint FogObjectShader;
	static GLuint FogModelShader;
	static GLuint StencilShader;
	static GLuint GeometryShader;
	static GLuint QuadTessShader;
	static GLuint TriTessShader;

	//Mesh ptrs
	static std::shared_ptr<MESH> CubeMesh;
	static std::shared_ptr<MESH> SphereMesh;
	static std::shared_ptr<MESH> PlaneMesh;
	static std::shared_ptr<MESH> QuadTessMesh;

	//Model ptrs
	static std::shared_ptr<Model> Player;

};