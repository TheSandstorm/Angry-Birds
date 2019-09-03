#include "MeshManager.h"

std::shared_ptr<MESH> MeshManager::CubeMesh = nullptr;
std::shared_ptr<MESH> MeshManager::SphereMesh = nullptr;
std::shared_ptr<MESH> MeshManager::PlaneMesh = nullptr;
std::shared_ptr<MESH> MeshManager::QuadTessMesh = nullptr;

std::shared_ptr<Model> MeshManager::Player = nullptr;

std::shared_ptr<MeshManager> MeshManager::ObjectManagerptr = nullptr;

GLuint MeshManager::ObjectShader;
GLuint MeshManager::ModelShader;
GLuint MeshManager::FogObjectShader;
GLuint MeshManager::FogModelShader;
GLuint MeshManager::CubeMapShader;
GLuint MeshManager::FogCubeMapShader;
GLuint MeshManager::StencilShader;
GLuint MeshManager::QuadTessShader;
GLuint MeshManager::TriTessShader;
GLuint MeshManager::GeometryShader;

MeshManager::MeshManager()
{
	GLuint VAO, VBO, EBO;
	FogCubeMapShader = ShaderLoader::CreateProgram(Utility::FogCubeMapShaderVert.data(), Utility::FogCubeMapShaderFrag.data());
	CubeMapShader = ShaderLoader::CreateProgram(Utility::CubeMapShaderVert.data(), Utility::CubeMapShaderFrag.data());
	FogModelShader = ShaderLoader::CreateProgram(Utility::ModelFogShaderVert.data(), Utility::ModelFogShaderFrag.data());
	FogObjectShader = ShaderLoader::CreateProgram(Utility::FogShaderVert.data(), Utility::FogShaderFrag.data());
	ObjectShader = ShaderLoader::CreateProgram(Utility::ObjectShaderVert.data(), Utility::ObjectShaderFrag.data());
	ModelShader = ShaderLoader::CreateProgram(Utility::ModelShaderVert.data(), Utility::ModelShaderFrag.data());
	StencilShader = ShaderLoader::CreateProgram(Utility::ObjectShaderVert.data(), Utility::SingleColorShaderFrag.data());
	TriTessShader = ShaderLoader::CreateProgram(Utility::TessShaderVert.data(), Utility::TessShaderFrag.data(), Utility::TessShaderTCSTri.data(), Utility::TessShaderTESTri.data());
	QuadTessShader = ShaderLoader::CreateProgram(Utility::TessShaderVert.data(), Utility::TessShaderFrag.data(), Utility::TessShaderTCSQuad.data(), Utility::TessShaderTESQuad.data());
	GeometryShader = ShaderLoader::CreateProgram(Utility::GeometryShaderVert.data() , Utility::ObjectShaderFrag.data(), Utility::GeometryShaderGeom.data());


	//Defines Cube Vertices
	GLfloat CubeVerts[] = {
		// Positions             // Normal Coords        // TexCoords
		// Front Face
		-1.0f, -1.0f, 1.0f,       0.0f, 0.0f, 1.0f,      0.0f, 0.0f,
		1.0f, -1.0f, 1.0f,        0.0f, 0.0f, 1.0f,      1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 1.0f,      1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,      0.0f, 0.0f, 1.0f,      0.0f, 1.0f,

		// Right Face
		1.0f, -1.0f, 1.0f,        1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
		1.0f, -1.0f, -1.0f,       1.0f, 0.0f, 0.0f,      1.0f, 0.0f,
		1.0f, 1.0f, -1.0f,      1.0f, 0.0f, 0.0f,      1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,       1.0f, 0.0f, 0.0f,      0.0f, 1.0f,

		// Back Face
		-1.0f, -1.0f, -1.0f,       0.0f, 0.0f, -1.0f,     0.0f, 0.0f,
		-1.0f, 1.0f, -1.0f,      0.0f, 0.0f, -1.0f,     1.0f, 0.0f,
		1.0f, 1.0f, -1.0f,     0.0f, 0.0f, -1.0f,     1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,      0.0f, 0.0f, -1.0f,     0.0f, 1.0f,

		// Left Face
		-1.0f, -1.0f, -1.0f,      -1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,       -1.0f, 0.0f, 0.0f,     1.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,      -1.0f, 0.0f, 0.0f,     1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,     -1.0f, 0.0f, 0.0f,     0.0f, 1.0f,

		// Top Face
		-1.0f, 1.0f, 1.0f,      0.0f, 1.0f, 0.0f,      0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,       0.0f, 1.0f, 0.0f,      1.0f, 0.0f,
		1.0f, 1.0f, -1.0f,        0.0f, 1.0f, 0.0f,      1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,       0.0f, 1.0f, 0.0f,      0.0f, 1.0f,

		// Bottom Face
		-1.0f, -1.0f, -1.0f,      0.0f, -1.0f, 0.0f,     0.0f, 0.0f,
		1.0f, -1.0f, -1.0f,       0.0f, -1.0f, 0.0f,     1.0f, 0.0f,
		1.0f, -1.0f, 1.0f,      0.0f, -1.0f, 0.0f,     1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,     0.0f, -1.0f, 0.0f,     0.0f, 1.0f,
	};

	//Defines Cube Indices
	GLuint CubeIndices[] = {
		0, 1, 2,		0, 2, 3,		// Front Face
		4, 5, 6,		4, 6, 7,		// Right Face
		8, 9, 10,		8, 10, 11,		// Back Face
		12, 13, 14,		12, 14, 15,		// Left Face
		16, 17, 18,		16, 18, 19,		// Top Face
		20, 21, 22,		20, 22, 23,		// Bottom Face
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	//Binding and setting buffer data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVerts), CubeVerts, GL_STATIC_DRAW);

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

	//Generating EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeIndices), CubeIndices, GL_STATIC_DRAW);

	//Setting the Mesh for the objects to use
	CubeMesh = make_shared<MESH>();
	CubeMesh->VAO = VAO;
	CubeMesh->IndicesCount = sizeof(CubeIndices);

	float radius = 1.0f;
	const int sections = 8;
	const int vertexAttrib = 8;
	const int indexPerQuad = 6;
	const float PI = 3.14159265359f;
	double phi = 0.0;
	double theta = 0.0;

	//Loops to generate the vertices of the sphere
	GLfloat SphereVerts[sections * sections * vertexAttrib];
	int offset = 0;

	for (int i = 0; i < sections; ++i) {
		theta = 0.0;
		for (int j = 0; j < sections; ++j) {
			float x = static_cast<float>(cos(phi) * sin(theta));
			float y = static_cast<float>(cos(theta));
			float z = static_cast<float>(sin(phi) * sin(theta));

			SphereVerts[offset++] = x * radius;
			SphereVerts[offset++] = y * radius;
			SphereVerts[offset++] = z * radius;

			SphereVerts[offset++] = x;
			SphereVerts[offset++] = y;
			SphereVerts[offset++] = z;

			SphereVerts[offset++] = (float)i / (sections - 1);
			SphereVerts[offset++] = (float)j / (sections - 1);

			theta += (PI / (sections - 1));
		}
		phi += (2 * PI) / (sections - 1);
	}

	//Loops to generate the indices of the sphere
	GLuint SphereIndices[sections * sections * indexPerQuad];
	offset = 0;
	for (int i = 0; i < sections; ++i) {
		for (int j = 0; j < sections; ++j) {
			SphereIndices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
			SphereIndices[offset++] = (((i + 1) % sections) * sections) + (j);
			SphereIndices[offset++] = (i * sections) + (j);

			SphereIndices[offset++] = (i * sections) + ((j + 1) % sections);
			SphereIndices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
			SphereIndices[offset++] = (i * sections) + (j);
		}
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SphereVerts), SphereVerts, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SphereIndices), SphereIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
#pragma endregion

	SphereMesh = std::make_shared<MESH>();
	SphereMesh->VAO = VAO;
	SphereMesh->IndicesCount = sizeof(SphereIndices);

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

	GLfloat points[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	-1.0, 1.0, 0.0f
	};
	int TessIndices = 4;
	glPatchParameteri(GL_PATCH_VERTICES, TessIndices);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0, 3,
		GL_FLOAT, GL_FALSE,
		3 * sizeof(GLfloat),
		0
	);

	QuadTessMesh = std::make_shared<MESH>();
	QuadTessMesh->VAO = VAO;
	QuadTessMesh->IndicesCount = TessIndices;

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	Player = make_shared<Model>(Utility::PlayerModel.data(), ModelShader);
}

MeshManager::~MeshManager() 
{
	CubeMesh = nullptr;
	SphereMesh = nullptr;
	PlaneMesh = nullptr;
	Player = nullptr;
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
	case SPHERE_OBJECT:
	{
		return SphereMesh;
	}
	case CUBE_OBJECT:
	{
		return CubeMesh;
	}
	case PLANE_OBJECT:
	{
		return PlaneMesh;
	}
	case QUAD_TESS_OBJECT:
	{
		return QuadTessMesh;
	}
	}
	return nullptr;
}

std::shared_ptr<Model> MeshManager::GetModel(Object_Attributes _ObjectType)
{
	if (_ObjectType == MODEL_PLAYER) return Player;

	return nullptr;
}

GLuint MeshManager::GetShaderProgram(Shader_Attributes _ShaderType)
{
	switch (_ShaderType)
	{
	case STANDARD_MODEL_SHADER:
	{
		return ModelShader;
	}
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
	case FOG_MODEL_SHADER:
	{
		return FogModelShader;
	}
	case FOG_CUBEMAP_SHADER:
	{
		return FogCubeMapShader;
	}
	case STENCIL_SHADER:
	{
		return StencilShader;
	}
	case GEOMETRY_SHADER:
	{
		return GeometryShader;
	}
	case TESS_QUAD_SHADER:
	{
		return QuadTessShader;
	}
	case TESS_TRI_SHADER:
	{
		return TriTessShader;
	}

	}
	wcout << "Failed to set shader\n";
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
