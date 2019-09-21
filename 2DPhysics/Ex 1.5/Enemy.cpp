#include "Enemy.h"
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

Enemy::Enemy(Transform _Transform, b2BodyType _Type, GLuint _ShaderProgram, GLuint _Texture)
{
	TransformSelf = _Transform;
	m_Radius = TransformSelf.Scale.x;
	m_SpawnPos = _Transform.Position;
	bType = _Type;
	ShaderProgram = _ShaderProgram;
	Texture = _Texture;
}

void Enemy::Init(b2World * _World)
{
	//Creating the rigidbody for the entity

	b2BodyDef BoxBodyDef;
	BoxBodyDef.type = bType;
	BoxBodyDef.active = true;
	BoxBodyDef.position.Set(TransformSelf.Position.x, TransformSelf.Position.y);
	BoxBodyDef.angle = TransformSelf.Rotation;

	//Spawning the body with the engine

	BoxBody = _World->CreateBody(&BoxBodyDef);

	//Defining physics parameters for the fixture

	b2FixtureDef FixtureDef;
	CircleBody.m_p.Set(0.0f, 0.0f);
	CircleBody.m_radius = m_Radius;
	FixtureDef.shape = &CircleBody;
	FixtureDef.density = 20.0f;
	FixtureDef.friction = 0.5f;
	FixtureDef.restitution = 0.001f;

	//Binding the fixture to the body

	BoxBody->CreateFixture(&FixtureDef);

	Data = new ObjectData;
	Data->ObjectType = "Pig";
	BoxBody->SetUserData(Data);

	auto a = static_cast<ObjectData*>(BoxBody->GetUserData())->ObjectType;

	//Translating the vertices supplied by Box2D into vertices usable by GLEW

	float verts[296]; //296 with tex
	int CurrentIndex = 0;
	verts[CurrentIndex++] = (CircleBody.m_p.x); //x
	verts[CurrentIndex++] = (CircleBody.m_p.y); //y
	verts[CurrentIndex++] = 0.0f; //z



	//color verts (the birds are all blue)

	verts[CurrentIndex++] = 1.0f;
	verts[CurrentIndex++] = 0.82f;
	verts[CurrentIndex++] = 0.0f;

	//tex quad center
	verts[CurrentIndex++] = 0.5f;
	verts[CurrentIndex++] = 0.5f;

	for (int i = 0; i < 36; ++i) {

		float angle = (i * 20.0f) * 3.1415f / 180.0f;
		verts[CurrentIndex++] = (CircleBody.m_radius * std::cos(angle)); //x
		verts[CurrentIndex++] = (CircleBody.m_radius * std::sin(angle)); //y
		verts[CurrentIndex++] = 0.0f; //z

		//color verts (the birds are all blue)

		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 0.82f;
		verts[CurrentIndex++] = 0.0f;

		//Finds the texture quad based on a circle

		verts[CurrentIndex++] = 0.5f*sin(angle) + 0.5f;
		verts[CurrentIndex++] = -0.5f*cos(angle) + 0.5f;

	}

	GLuint IndicesCircle[] =

	{

		0,1,2,

		0,2,3,

		0,3,4,

		0,4,5,

		0,5,6,

		0,6,7,

		0,7,8,

		0,8,9,

		0,9,10,

		0,10,11,

		0,11,12,

		0,12,13,

		0,13,14,

		0,15,16,

		0,16,17,

		0,18,19,

		0,19,20,

		0,20,21,

		0,22,23,

		0,23,24,

		0,24,25,

		0,25,26,

		0,26,27,

		0,27,28,

		0,28,29,

		0,30,31,

		0,31,32,

		0,32,33,

		0,33,34,

		0,34,35,

		0,35,36,

	};

	CurrentIndex = 0;

	//Generating and binding the buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	//Generating EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndicesCircle), IndicesCircle, GL_STATIC_DRAW);


	IndicesCount = sizeof(IndicesCircle);

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

void Enemy::Process()
{

}

void Enemy::Render()
{
	//Binding appropriate buffers and rendering

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(ShaderProgram);
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	//Creating the transformation matrices
	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), glm::vec3(BoxBody->GetPosition().x, BoxBody->GetPosition().y, 0.0f));
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), BoxBody->GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 10.0f));

	//Creating the MVP using the translation matrices and orthographic projection
	glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;
	glm::mat4 proj = glm::ortho(0.0f, float(Utility::SCR_WIDTH) / float(Utility::Ratio), 0.0f, float(Utility::SCR_HEIGHT) / float(Utility::Ratio)); // Camera needs to replace this
	glm::mat4 MVP = proj * ModelMatrix;


	//Sending the texture to the GPU via uniform
	glUniform1i(glGetUniformLocation(ShaderProgram, "tex"), 0);

	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	//Setting a memory pointer in the shader program to the MVP
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
	glUniform3fv(glGetUniformLocation(ShaderProgram, "camPos"), 1, glm::value_ptr(glm::vec3(0, 0, 0)));

	//Drawing the entity
	glDrawElements(GL_TRIANGLES, IndicesCount, GL_UNSIGNED_INT, 0);
	glDisable(GL_BLEND);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Enemy::SetPosition(b2Vec2 _Pos)
{
	TransformSelf.Position = _Pos;
}
