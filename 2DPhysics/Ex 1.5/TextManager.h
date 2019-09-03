#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

//Includes
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

//Library
#include <map>
#include <string>
#include <iostream>

//Local Includes
#include "ShaderLoader.h"
#include "Utility.h"

struct FontChar
{
	GLuint	TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};

class CTextLabel
{

public:
	CTextLabel();
	CTextLabel(std::string newText, std::string newFont, glm::vec2 pos, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float scale = 1.0f);
	~CTextLabel() { Characters.clear(); };

	void Render();
	void SetText(std::string newText) { text = newText; };
	void SetColor(glm::vec3 newColor) { color = newColor; };
	void SetScale(GLfloat newScale) { scale = newScale; };
	void SetPosition(glm::vec2 newPostition) { position = newPostition; };
private:
	GLuint GenerateTexture(FT_Face face);

	std::string text;
	GLfloat scale;
	glm::vec3 color;
	glm::vec2 position;

	GLuint VAO, VBO, program;
	glm::mat4 proj;
	std::map<GLchar, FontChar> Characters;
};
#endif