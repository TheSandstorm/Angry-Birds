#pragma once
#include <glew.h>
#include <freeglut.h>
#include <glm.hpp>

#include <vector>

class Triangle
{
public:
	void Render(GLuint _Program)
	{
		if (isValid == true)
		{
			glUseProgram(_Program);
			glBindVertexArray(VAO);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
		};
	};
	void ResetPoints()
	{
		Points.clear();
		isValid = false;
	}
	void Process()
	{
		if (Points.size() == 18 && isValid == false)
		{
			isValid = true;
			std::copy(Points.begin(), Points.end(), verts);

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
			glBindVertexArray(VAO);

			//Enabling the positional floats
			glVertexAttribPointer(
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				6 * sizeof(GLfloat),
				(GLvoid*)0
			);

			glEnableVertexAttribArray(0);

			//Enabling Color Floats
			glVertexAttribPointer(
				1,
				3,
				GL_FLOAT,
				GL_FALSE,
				6 * sizeof(GLfloat),
				(GLvoid*)(3 * sizeof(GLfloat))
			);
			glEnableVertexAttribArray(1);
		}
	};
	void AddPoint(glm::vec2 _Point, glm::vec3 _Color)
	{
		if (Points.size() <= 18)
		{
			//Position Setting
			Points.push_back(_Point.x); // X
			Points.push_back(_Point.y); // Y
			Points.push_back(0.0f); // Z
			//Color Setting
			Points.push_back(_Color.x); // R
			Points.push_back(_Color.y); // G
			Points.push_back(_Color.z); // B
		}
	};
	std::vector<float>& GetPoints() { return Points; };
	bool isValid = false;
private:
	GLuint VBO;
	GLuint VAO;

	std::vector<float> Points;
	float verts[18];
};