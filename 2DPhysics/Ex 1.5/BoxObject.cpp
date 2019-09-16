#include "BoxObject.h"

Box::Box()
{
}

Box::~Box()
{
}

Box::Box(Transform _Transform, b2BodyType _Type, GLuint _ShaderProgram, GLuint _Texture)
{
	TransformSelf = _Transform;
	bType = _Type;
	ShaderProgram = _ShaderProgram;
}

void Box::Init(b2World* _World)
{
	//Creating the rigidbody
	b2BodyDef BoxBodyDef;
	BoxBodyDef.type = bType;
	BoxBodyDef.active = true;
	BoxBodyDef.position.Set(TransformSelf.Position.x, TransformSelf.Position.y);
	BoxBodyDef.angle = TransformSelf.Rotation;

	//Spawning the body to the world
	BoxBody = _World->CreateBody(&BoxBodyDef);

	//Defining physics parameters for the fixture
	b2FixtureDef FixtureDef;
	DynamicBox.SetAsBox(TransformSelf.Scale.x, TransformSelf.Scale.y);
	FixtureDef.density = 2.0f;
	FixtureDef.friction = 1.0f;
	FixtureDef.restitution = 0.0f;

	//Binding the fixture to the Body
	BoxBody->CreateFixture(&FixtureDef);

	//Data Set to object
	Data = new ObjectData;
	Data->ObjectType = "Block";
	BoxBody->SetUserData(Data);

	//GLEW goes HERE. Need To figure out how to get textures to work with this method
	//Note We are going to use the fixtures vertices
	float verts[32];
	int CurrentIndex = 0;
	int TexIndex = 0;
	float texCoord[] =
	{
		0.0f,0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};
	for (int i = 0; i < DynamicBox.m_count; i++) {
		verts[CurrentIndex++] = (DynamicBox.m_vertices[i].x); //x
		verts[CurrentIndex++] = (DynamicBox.m_vertices[i].y); //y
		verts[CurrentIndex++] = 0.0f; //z

		//color verts
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 0.07f;
		verts[CurrentIndex++] = 0.0f;

		//Texture coords
		verts[CurrentIndex++] = texCoord[TexIndex++];
		verts[CurrentIndex++] = texCoord[TexIndex++];
	}

	GLuint Indices[] = {
		0, 1, 2,		0, 2, 3		// Front Face
	};

	//Generating and binding the buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * (8 * DynamicBox.m_count), verts, GL_STATIC_DRAW);
	//Generating EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	glBindVertexArray(VAO);



	//Enabling the positional floats
	glVertexAttribPointer(
		0, 3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)0
	);
	glEnableVertexAttribArray(0);

	//Enabling Color Floats
	glVertexAttribPointer(
		1, 3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat))
	);

	//Enabling the Texture floats
	glVertexAttribPointer(
		2, 2, 
		GL_FLOAT, 
		GL_FALSE, 
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat))
	);
	glEnableVertexAttribArray(2);

	//CleanUp (Unbinding)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Box::Process()
{
}

void Box::Render()
{
	//Creating the transformation matrices
	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), glm::vec3(BoxBody->GetPosition().x, BoxBody->GetPosition().y, 0.0f));
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), BoxBody->GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 10.0f));

	//Creating the MVP using the translation matrices and orthographic projection
	glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;
	glm::mat4 proj = glm::ortho(0.0f, float(Utility::SCR_WIDTH), 0.0f, float(Utility::SCR_HEIGHT)); // Camera needs to replace this
	glm::mat4 MVP = proj * ModelMatrix;

	//Setting a memory pointer in the shader program to the MVP
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

	//Binding appropriate buffers and rendering
	glUseProgram(ShaderProgram);
	glBindVertexArray(VAO);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
