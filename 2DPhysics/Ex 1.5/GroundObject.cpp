#include "GroundObject.h"

Ground::Ground()
{
}

Ground::Ground(Transform _Transform, b2BodyType _bodytype, GLuint _ShaderProgram, GLuint _Texture)
{
	TransformSelf = _Transform;
	bType = _bodytype;
	ShaderProgram = _ShaderProgram;
	Texture = _Texture;
}

Ground::~Ground()
{
}

void Ground::Init(b2World* _World)
{
	//Creating the rigidbody for the entity
	b2BodyDef BoxBodyDef;
	BoxBodyDef.type = bType;
	BoxBodyDef.active = true;
	BoxBodyDef.position.Set(TransformSelf.Position.x, TransformSelf.Position.y);
	BoxBodyDef.angle = TransformSelf.Rotation;
	BoxBodyDef.gravityScale = 0;

	//Spawning the body with the engine
	BoxBody = _World->CreateBody(&BoxBodyDef);

	//Defining physics parameters for the fixture
	b2FixtureDef FixtureDef;
	DynamicBox.SetAsBox(TransformSelf.Scale.x, TransformSelf.Scale.y);
	FixtureDef.shape = &DynamicBox;
	FixtureDef.density = 300.0f;
	FixtureDef.friction = 1.0f;
	FixtureDef.restitution = 0.001f;

	//Binding the fixture to the body
	BoxBody->CreateFixture(&FixtureDef);

	Data = new ObjectData;
	Data->ObjectType = "GroundBlock";
	BoxBody->SetUserData(Data);

	//Translating the vertices supplied by Box2D into vertices usable by GLEW
	float verts[24];
	int CurrentIndex = 0;
	for (int i = 0; i < DynamicBox.m_count; i++) {
		verts[CurrentIndex++] = (DynamicBox.m_vertices[i].x); //x
		verts[CurrentIndex++] = (DynamicBox.m_vertices[i].y); //y
		verts[CurrentIndex++] = 0.0f; //z

		//color verts
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 1.0f;
	}

	//generating and binding the buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * (6 * DynamicBox.m_count), verts, GL_STATIC_DRAW);
	glBindVertexArray(VAO);

	//Enabling the positional floats
	glVertexAttribPointer(
		0, 3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)0
	);
	glEnableVertexAttribArray(0);

	//Enabling Color Floats
	glVertexAttribPointer(
		1, 3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat))
	);
	glEnableVertexAttribArray(1);

	//CleanUp (Unbinding)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Ground::Process()
{
}

void Ground::Render()
{
}
