#include "BirdObject.h"

b2BodyDef bodyDef;	b2PolygonShape birdShape;
b2BodyDef slingBodyDef;	b2PolygonShape slingShape;
GLuint birdProgram;
GLuint slingProgram;

GLuint VAObirb, VBObirb, EBObirb;
GLuint VAOsling, VBOsling, EBOsling;

b2Body* birbBody;
b2Body* slingBody;

b2MouseJointDef MouseJointDef;
b2MouseJoint* MouseJoint;

GLuint Indices[] = {
0, 1, 2,		0, 2, 3		// Front Face
};

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
	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), glm::vec3(birbBody->GetPosition().x, birbBody->GetPosition().y, 0.0f));
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), birbBody->GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), glm::vec3(50, 1, 5));

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



	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(slingProgram);
	glBindVertexArray(VAOsling);
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, Texture);
	//Creating the transformation matrices
	glm::mat4 SlingTranslationMatrix = glm::translate(glm::mat4(), glm::vec3(slingBody->GetPosition().x, slingBody->GetPosition().y, 0.0f));
	glm::mat4 SlingRotationMatrix = glm::rotate(glm::mat4(), slingBody->GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 SlingScaleMatrix = glm::scale(glm::mat4(), glm::vec3(50, 1, 5));

	//Creating the MVP using the translation matrices and orthographic projection
	glm::mat4 slingModelMatrix = SlingTranslationMatrix * SlingRotationMatrix * SlingScaleMatrix;
	glm::mat4 slingproj = glm::ortho(0.0f, float(Utility::SCR_WIDTH), 0.0f, float(Utility::SCR_HEIGHT)); // Camera needs to replace this
	glm::mat4 slingMVP = slingproj * slingModelMatrix;


	//Sending the texture to the GPU via uniform
//	glUniform1i(glGetUniformLocation(birdProgram, "tex"), 0);

	glUniformMatrix4fv(glGetUniformLocation(slingProgram, "model"), 1, GL_FALSE, glm::value_ptr(slingModelMatrix));
	//Setting a memory pointer in the shader program to the MVP
	glUniformMatrix4fv(glGetUniformLocation(slingProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(slingMVP));
	glUniform3fv(glGetUniformLocation(slingProgram, "camPos"), 1, glm::value_ptr(glm::vec3(0, 0, 0)));

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
	bodyDef.position.Set(500, 500);
	bodyDef.angle = 0;
	bodyDef.active = true;

	birbBody = _World ->CreateBody(&bodyDef);

	birdShape.SetAsBox(5, 5);

	b2FixtureDef birdFixtureDef;
	birdFixtureDef.shape = &birdShape;
	birdFixtureDef.density = 1.0f;
	birdFixtureDef.friction = 1.0f;
	birdFixtureDef.restitution = 0.0f;

	birbBody->CreateFixture(&birdFixtureDef);


	//DEBUG
	std::cout << "Got through all of the birb initilisation" << std::endl;

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


//what the bird does from frame to frame
void Bird::processBirb(b2World* _world, float x, float y)
{

	if (inputManager->MouseArray[MOUSE_LEFT] == HELD) {

		MouseJointDef.bodyA = slingBody;
		MouseJointDef.bodyB = birbBody;
		MouseJointDef.dampingRatio = 6.0f;
		MouseJointDef.frequencyHz = 1.0f;
		MouseJointDef.maxForce = (float)(100.0f);
		MouseJointDef.target.Set(x, y);
		MouseJointDef.collideConnected = false;
		MouseJoint = (b2MouseJoint*)_world->CreateJoint(&MouseJointDef);
		std::cout << "Created Joint" << std::endl;


		if ((birbBody->GetPosition() - slingBody->GetPosition()).Length() >= 50.0f) {
			b2Vec2 d = birbBody->GetPosition() - slingBody->GetPosition();
			d.Normalize();
			d *= 0.99f;
			birbBody->SetTransform(d + slingBody->GetPosition(), 0.0f);
			MouseJoint->SetTarget(d + slingBody->GetPosition());
			std::cout << "follow Joint" << std::endl;
		}
		else {
			MouseJoint->SetTarget(b2Vec2(x, y));
			birbBody->ApplyLinearImpulse(b2Vec2(200.0f, 200.0f), birbBody->GetWorldCenter(), true);
		}
	}
	else if (MouseJoint) {
			_world->DestroyJoint(MouseJoint);
			MouseJoint = nullptr;
			std::cout << "destroy Joint" << std::endl;
			birbBody->ApplyLinearImpulse(b2Vec2(400.0f, 200.0f), birbBody->GetWorldCenter(), true);
		}
}



void Bird::initSlingShot(b2World * _World)
{

	//setting the bird to be a dynamic rigidbody
	slingBodyDef.type = b2_staticBody;
	slingBodyDef.position.Set(450, 450);
	slingBodyDef.angle = 0;
	slingBodyDef.active = true;
	slingBodyDef.gravityScale = 0;

	slingBody = _World->CreateBody(&slingBodyDef);

	slingShape.SetAsBox(5, 5);

	b2FixtureDef slingFixtureDef;
	slingFixtureDef.shape = &slingShape;
	slingFixtureDef.density = 1.0f;
	slingFixtureDef.friction = 1.0f;
	slingFixtureDef.restitution = 0.0f;

	slingBody->CreateFixture(&slingFixtureDef);


	//DEBUG
	std::cout << "Got through all of the sling initilisation" << std::endl;

	//possibly render the birds

	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};


	slingProgram = ShaderLoader::CreateProgram("Resources/Shaders/FogCubeShader.vs", "Resources/Shaders/FogCubeShader.fs");

	//Generating and binding the buffers
	glGenVertexArrays(1, &VAOsling);
	glGenBuffers(1, &VBOsling);
	glGenBuffers(1, &EBOsling);

	glBindVertexArray(VAOsling);
	glBindBuffer(GL_ARRAY_BUFFER, VBOsling);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Generating EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOsling);
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
