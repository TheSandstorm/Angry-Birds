#include "ProgramManager.h"
std::shared_ptr<CProgramManager> CProgramManager::SceneManagerPtr;

CProgramManager::CProgramManager()
{
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glLineWidth(3.0f);
	//Creating the shaders
	shaderProgram = SL->CreateProgram(
		const_cast<char*>("Resources/Shaders/Vertex Shader.vs"),
		const_cast<char*>("Resources/Shaders/Fragment Shader.fs")
	);
	glClearColor(1.0f, 0.6f, 0.0f, 1.0f); //Orange
}
CProgramManager::~CProgramManager()
{
	delete IM; IM = nullptr;
	delete SL; SL = nullptr;
	shaderProgram = 0;
}

void CProgramManager::DestoryInstance()
{
	SceneManagerPtr = nullptr;
}

std::shared_ptr<CProgramManager> CProgramManager::GetInstance()
{
	if (SceneManagerPtr == nullptr) SceneManagerPtr = std::shared_ptr<CProgramManager>(new CProgramManager());
	return SceneManagerPtr;
}

void CProgramManager::Update()
{
	char Result = IM->ProcessKeys();
}

void CProgramManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::vec3 CProgramManager::CrossProduct(glm::vec3 A, glm::vec3 B)
{
	return glm::vec3((A.y*B.z - A.z * B.y), (A.z*B.x - A.x * B.z), (A.x*B.y - A.y * B.x));
}
