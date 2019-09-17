#include "BirdObject.h"

b2BodyDef bodyDef;	b2PolygonShape birdShape;
GLuint birdProgram;

GLuint VAObirb, VBObirb, EBObirb;

GLuint Indices[] = {
0, 1, 2,		0, 2, 3		// Front Face
};


Bird::Bird()
{

}

void Bird::RenderBird()
{

	//Binding appropriate buffers and rendering

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(birdProgram);
	glBindVertexArray(VAObirb);
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, Texture);
	//Creating the transformation matrices
	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), glm::vec3(bodyDef.position.x, bodyDef.position.y, 0.0f));
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(),bodyDef.angle , glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), glm::vec3(100.0f, 100.0f, 100.0f));

	//Creating the MVP using the translation matrices and orthographic projection
	glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;
	glm::mat4 proj = glm::ortho(0.0f, float(Utility::SCR_WIDTH), 0.0f, float(Utility::SCR_HEIGHT)); // Camera needs to replace this
	glm::mat4 MVP = proj * ModelMatrix;


	//Sending the texture to the GPU via uniform
//	glUniform1i(glGetUniformLocation(birdProgram, "tex"), 0);

	glUniformMatrix4fv(glGetUniformLocation(birdProgram, "model"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	//Setting a memory pointer in the shader program to the MVP
	glUniformMatrix4fv(glGetUniformLocation(birdProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
	glUniform3fv(glGetUniformLocation(birdProgram, "camPos"), 1, glm::value_ptr(glm::vec3(0, 0, 0)));

	//Drawing the entity
	glDrawElements(GL_TRIANGLES, sizeof(Indices), GL_UNSIGNED_INT, 0);
	glDisable(GL_BLEND);
	glBindVertexArray(0);
	glUseProgram(0);
}


void Bird::initBird(b2World* _World)
{

	//setting the bird to be a dynamic rigidbody
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0, 20);
	bodyDef.angle = 0;

	b2Body* dynamicBody = _World ->CreateBody(&bodyDef);

	birdShape.SetAsBox(1, 1);

	b2FixtureDef birdFixtureDef;
	birdFixtureDef.shape = &birdShape;
	birdFixtureDef.density = 1;
	dynamicBody->CreateFixture(&birdFixtureDef);

	//DEBUG
	std::cout << "Got through all of the initilisation" << std::endl;

	//possibly render the birds
	
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};


	birdProgram = ShaderLoader::CreateProgram("Resources/Shaders/FogCubeShader.vs", "Resources/Shaders/FogCubeShader.fs");

	//Generating and binding the buffers
	glGenVertexArrays(1, &VAObirb);
	glGenBuffers(1, &VBObirb);
	glGenBuffers(1, &EBObirb);

	glBindVertexArray(VAObirb);
	glBindBuffer(GL_ARRAY_BUFFER, VBObirb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Generating EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBObirb);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

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

	//CleanUp (Unbinding)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
