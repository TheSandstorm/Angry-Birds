#include "TextManager.h"

//temp Constructor
CTextLabel::CTextLabel()
{

}
//Init the class fully
CTextLabel::CTextLabel(std::string newText, std::string newFont, glm::vec2 pos, glm::vec3 color, float scale )
{
	text = newText;
	SetColor(color);
	SetScale(scale);
	SetPosition(pos);

	GLfloat halfScreenWidth = (GLfloat)Utility::SCR_WIDTH * 0.5f;
	GLfloat halfScreenHeight = (GLfloat)Utility::SCR_HEIGHT * 0.5f;
	proj = glm::ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight);
	program = ShaderLoader::CreateProgram("Resources/Shaders/Text.vs", "Resources/Shaders/Text.fs");

	FT_Library ft;
	FT_Face face;
	
	FT_Error FT_Init_FreeType(FT_Library* aLibrary);
	FT_Error FT_New_Face(FT_Library library, const char* filepath, FT_Long face_index, FT_Face* aFace);


	if (FT_Init_FreeType(&ft) != 0)
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}

	if (FT_New_Face(ft, newFont.c_str(), 0, &face) != 0)
	{
		std::cout << "ERROR::FREETYPE: Failed to Load font" << std::endl;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte character = 0; character < 128; character++)
	{
		if (FT_Load_Char(face, character, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
			continue;
		}

		GLuint texture = GenerateTexture(face);

		FontChar fontChar = { texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::ivec2(face->glyph->bitmap_left,face->glyph->bitmap_top), (GLuint)face->glyph->advance.x };
		Characters.insert(std::pair<GLchar, FontChar>(character, fontChar));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
//Renders the text on to the screen
void CTextLabel::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(program);
	glUniform3f(glGetUniformLocation(program, "textColor"), color.x, color.y, color.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
	glBindVertexArray(VAO);

	glActiveTexture(GL_TEXTURE0);
	glm::vec2 textPos = position;
	float initialx = textPos.x; //Holds the x pos for menu
	for (std::string::const_iterator character = text.begin(); character != text.end(); character++)
	{
		FontChar fontChar = Characters[*character];
		GLfloat xpos = textPos.x + fontChar.Bearing.x *scale;
		GLfloat ypos = textPos.y - (fontChar.Size.y - fontChar.Bearing.y) * scale;
		GLfloat charWidth = fontChar.Size.x * scale;
		GLfloat charHeight = fontChar.Size.y * scale;

		if (*character == 10)// slash key in code
		{
			textPos.x = (initialx - 6);
			textPos.y -= (fontChar.Advance >> 5) * scale * 1.1f;
		}
		else
		{
			GLfloat vertices[6][4] = {
				{xpos, ypos + charHeight, 0.0, 0.0 }, {xpos, ypos, 0.0, 1.0}, {xpos + charWidth, ypos, 1.0, 1.0},
				{xpos, ypos + charHeight, 0.0, 0.0 }, {xpos + charWidth, ypos, 1.0, 1.0} , {xpos + charWidth, ypos + charHeight, 1.0, 0.0},
			};
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			glBindTexture(GL_TEXTURE_2D, fontChar.TextureID);
			glUniform1i(glGetUniformLocation(program, "tex"), 0);	
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			textPos.x += (fontChar.Advance >> 6) * scale;
		}
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}
GLuint CTextLabel::GenerateTexture(FT_Face face)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, 
				face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}
