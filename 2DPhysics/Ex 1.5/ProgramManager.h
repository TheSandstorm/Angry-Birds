#pragma once
#include "ShaderLoader.h"
#include "Triangle.h"
#include "Line.h"
#include "InputManger.h"

class CProgramManager
{
public:
	~CProgramManager();
	static void DestoryInstance();
	static std::shared_ptr<CProgramManager> GetInstance();

	void Update();

	void Render();	

private:
	CProgramManager();
	static std::shared_ptr<CProgramManager> SceneManagerPtr;
	GLuint shaderProgram;
	CInputManager* IM = new CInputManager;
	ShaderLoader* SL = new ShaderLoader;

	Line* line0 = new Line;
	Triangle* tri0 = new Triangle;

	Triangle* tri1 = new Triangle;
	Triangle* tri2 = new Triangle;
	Triangle* tri3 = new Triangle;
	int CurrentPoint = 0;
	void GenerateResultingTris(Line _line, Triangle _tri);
	glm::vec3 CrossProduct(glm::vec3 A, glm::vec3 B);
};