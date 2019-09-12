#include "ProgramManager.h"
#include "Utility.h"
#include <iostream>
#include <glew.h>
#include <freeglut.h>
using namespace std;


void Update()
{
	CProgramManager::GetInstance()->Update();
	glutPostRedisplay();
}

void Render()
{
	CProgramManager::GetInstance()->Render();
	glutSwapBuffers();
}

void Exit()
{
	CProgramManager::DestoryInstance();
	exit(1);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(ScreenInfo::SCR_HEIGHT, ScreenInfo::SCR_WIDTH);
	glutCreateWindow("MEME Birds HD");
	glEnable(GL_MULTISAMPLE);
	//Sets up all gl function callbacks based on pc hardware
	if (glewInit() != GLEW_OK)
	{
		//If glew setup failed thenapplication will not run graphics correctly
		cout << "Glew Initialization Failed. Aborting Application." << endl;
		system("pause");
	}
	CProgramManager::GetInstance();

	glutDisplayFunc(Render);
	glutIdleFunc(Update);	
	glutIgnoreKeyRepeat(1);
	glutCloseFunc(Exit);
	glutMainLoop();
	return (0);
}