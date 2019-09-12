#include "MeshManager.h"

std::shared_ptr<MESH> MeshManager::PlaneMesh = nullptr;

std::shared_ptr<MeshManager> MeshManager::ObjectManagerptr = nullptr;

GLuint MeshManager::ObjectShader;
GLuint MeshManager::FogObjectShader;
GLuint MeshManager::CubeMapShader;
GLuint MeshManager::FogCubeMapShader;
GLuint MeshManager::StencilShader;

MeshManager::MeshManager()
{
	GLuint VAO, VBO, EBO;
	FogCubeMapShader = ShaderLoader::CreateProgram(Utility::FogCubeMapShaderVert.data(), Utility::FogCubeMapShaderFrag.data());
	CubeMapShader = ShaderLoader::CreateProgram(Utility::CubeMapShaderVert.data(), Utility::CubeMapShaderFrag.data());
	FogObjectShader = ShaderLoader::CreateProgram(Utility::FogShaderVert.data(), Utility::FogShaderFrag.data());
	ObjectShader = ShaderLoader::CreateProgram(Utility::ObjectShaderVert.data(), Utility::ObjectShaderFrag.data());
	StencilShader = ShaderLoader::CreateProgram(Utility::ObjectShaderVert.data(), Utility::SingleColorShaderFrag.data());

	GLfloat PlaneVerts[] = {
		// Positions             // Normal Coords        // TexCoords
		// Front Face
		-1.0f, 1.0f, 0.0f,       0.0f, 0.0f, 1.0f,      0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,        0.0f, 0.0f, 1.0f,      2.0f, 0.0f,
		1.0f, -1.0f, 0.0f,       0.0f, 0.0f, 1.0f,      2.0f, 2.0f,
		-1.0f, -1.0f, 0.0f,      0.0f, 0.0f, 1.0f,      0.0f, 2.0f,
	};

	//Defining Cube Indices
	GLuint PlaneIndices[] = {
		0, 1, 2,		0, 2, 3		// Front Face
	};

	//Generating buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	//Binding and setting buffer data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PlaneVerts), PlaneVerts, GL_STATIC_DRAW);

	//Generating EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(PlaneIndices), PlaneIndices, GL_STATIC_DRAW);

	//Enabling the positional floats
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Enabling Normal Floats
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Enabling the Texture floats
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


#pragma endregion

	PlaneMesh = std::make_shared<MESH>();
	PlaneMesh->VAO = VAO;
	PlaneMesh->IndicesCount = sizeof(PlaneIndices);
#pragma endregion
}

MeshManager::~MeshManager() 
{
	PlaneMesh = nullptr;
}

std::shared_ptr<MeshManager> MeshManager::GetInstance()
{
	if (ObjectManagerptr == nullptr) 
	{
		ObjectManagerptr = std::shared_ptr<MeshManager>(new MeshManager());
	}
	return ObjectManagerptr;
}

void MeshManager::DestroyInstance()
{
	ObjectManagerptr = nullptr;
}

std::shared_ptr<MESH> MeshManager::GetMesh(Object_Attributes _ObjectType)
{
	switch (_ObjectType)
	{
	case PLANE_OBJECT:
	{
		return PlaneMesh;
	}
	}
	return nullptr;
}

GLuint MeshManager::GetShaderProgram(Shader_Attributes _ShaderType)
{
	switch (_ShaderType)
	{
	case STANDARD_SHADER:
	{
		return ObjectShader;
	}
	case STANDARD_CUBEMAP_SHADER:
	{
		return CubeMapShader;
	}
	case FOG_SHADER:
	{
		return FogObjectShader;
	}
	case FOG_CUBEMAP_SHADER:
	{
		return FogCubeMapShader;
	}
	case STENCIL_SHADER:
	{
		return StencilShader;
	}

	}
	std::wcout << "Failed to set shader\n";
	return NULL;
}

GLuint MeshManager::SetTexture(const char* _Texture)
{
	GLuint Texture;
	int width, height;

	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);

	//Setting Texture wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Setting texture filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Getting the image from filepath
	unsigned char* image = SOIL_load_image(
		_Texture,
		&width,
		&height,
		0,
		SOIL_LOAD_RGBA
	);

	//Generating the texture from image data
	if (image)
	{
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			width, height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image
		);
		//Generating mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::wcout << L"Failed to load Texture\n";
	}
	//Freeing up data
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return Texture;
}
