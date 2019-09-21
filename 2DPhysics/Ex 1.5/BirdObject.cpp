#include "BirdObject.h"
#include "Object.h"

Bird::Bird()

{

}



Bird::~Bird()

{

}



Bird::Bird(Transform _Transform, b2BodyType _Type, GLuint _ShaderProgram, GLuint _Texture)

{

	//Don't use the y scale for the class type

	TransformSelf = _Transform;

	m_Radius = TransformSelf.Scale.x;

	m_SpawnPos = _Transform.Position;

	bType = _Type;

	ShaderProgram = _ShaderProgram;

	Texture = _Texture;

}



void Bird::Init(b2World* _World)

{

	m_bEnableDecay = false;

	m_fDecayTimer = 0.0f;

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

	Data->ObjectType = "Bird";

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

	//for (int i = 1; i < 37; i++)

	//{

	//	IndicesCircle[CurrentIndex++] = 0;

	//	IndicesCircle[CurrentIndex++] = i;

	//	indices[CurrentIndex++] = i + 1;

	//}



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



void Bird::Process()
{
}



void Bird::Render()
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



void Bird::SetPosition(b2Vec2 _Pos)

{

	TransformSelf.Position = _Pos;

}

////what the bird does from frame to frame
//void Bird::processBirb(b2World* _world, float x, float y)
//{
//#pragma region distance joint
//	
//	//birbBody->ApplyLinearImpulse(b2Vec2(10, 10), birbBody->GetWorldCenter(), true);
//
//	b2DistanceJointDef jointDef;
//	jointDef.Initialize(birbBody, slingBody, birbBody->GetLocalCenter(), slingBody->GetLocalCenter());
//	jointDef.collideConnected = false;
//	jointDef.frequencyHz = 500.0f;
//	jointDef.dampingRatio = 1.0f;
//
//	b2DistanceJoint* m_distJoint = (b2DistanceJoint*)_world->CreateJoint(&jointDef);
//
//#pragma endregion
//
//#pragma region revoluteJoint
//
//
//	//b2RevoluteJointDef revoluteJointDef;
//	//revoluteJointDef.bodyA = birbBody;
//	//revoluteJointDef.bodyB = slingBody;
//	//revoluteJointDef.collideConnected = false;
//	//revoluteJointDef.localAnchorA.Set(2, 2);//the top right corner of the box
//	//revoluteJointDef.localAnchorB.Set(-5, -5);//center of the circle
//	//b2RevoluteJoint* m_joint = (b2RevoluteJoint*)_world->CreateJoint(&revoluteJointDef);
//
//	//revoluteJointDef.enableMotor = true;
//	//revoluteJointDef.maxMotorTorque = 15000;
//	//revoluteJointDef.motorSpeed = 9999999999;
//	//birbBody->ApplyAngularImpulse(1, true);
//	//birbBody->ApplyTorque(20, true); 
//
//#pragma endregion
//	//	}
//			//
//
//			//MouseJointDef.bodyA = slingBody;
//			//MouseJointDef.bodyB = birbBody;
//			//MouseJointDef.dampingRatio = 6.0f;
//			//MouseJointDef.frequencyHz = 1.0f;
//			//MouseJointDef.maxForce = (float)(100.0f);
//			//MouseJointDef.target.Set(x, y);
//			//MouseJointDef.collideConnected = false;
//			//MouseJoint = (b2MouseJoint*)_world->CreateJoint(&MouseJointDef);
//			//std::cout << "Created Joint" << std::endl;
//
//
//		//	if ((birbBody->GetPosition() - slingBody->GetPosition()).Length() >= 50.0f) {
//		//		b2Vec2 d = birbBody->GetPosition() - slingBody->GetPosition();
//		//		d.Normalize();
//		//		d *= 0.99f;
//		//		birbBody->SetTransform(d + slingBody->GetPosition(), 0.0f);
//		//		MouseJoint->SetTarget(d + slingBody->GetPosition());
//		//		std::cout << "follow Joint" << std::endl;
//		//	}
//		//	else {
//		//		MouseJoint->SetTarget(b2Vec2(x, y));
//		//		birbBody->ApplyLinearImpulse(b2Vec2(200.0f, 200.0f), birbBody->GetWorldCenter(), true);
//		//	}
//		//}
//		//else if (MouseJoint) {
//		//		_world->DestroyJoint(MouseJoint);
//		//		MouseJoint = nullptr;
//		//		std::cout << "destroy Joint" << std::endl;
//		//		birbBody->ApplyLinearImpulse(b2Vec2(400.0f, 200.0f), birbBody->GetWorldCenter(), true);
//			//}
//}
//
//
//
//void Bird::initSlingShot(b2World * _World)
//{
//
//	//setting the bird to be a dynamic rigidbody
//	slingBodyDef.type = b2_dynamicBody;
//	slingBodyDef.position.Set(600, 600);
//	slingBodyDef.angle = 0;
//	slingBodyDef.active = true;
//	slingBodyDef.gravityScale = 0;
//
//	slingBody = _World->CreateBody(&slingBodyDef);
//
//	slingShape.SetAsBox(2, 2);
//
//	b2FixtureDef slingFixtureDef;
//	slingFixtureDef.shape = &slingShape;
//	slingFixtureDef.density = 500.0f;
//	slingFixtureDef.friction = 1.0f;
//	slingFixtureDef.restitution = 0.0f;
//
//	slingBody->CreateFixture(&slingFixtureDef);
//
//
//	//DEBUG
//	std::cout << "Got through all of the sling initilisation" << std::endl;
//
//	//possibly render the birds
//
//	float vertices[] = {
//	-0.5f, -0.5f, 0.0f,
//	 0.5f, -0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f
//	};
//
//
//	slingProgram = ShaderLoader::CreateProgram("Resources/Shaders/FogCubeShader.vs", "Resources/Shaders/FogCubeShader.fs");
//
//	//Generating and binding the buffers
//	glGenVertexArrays(1, &VAOsling);
//	glGenBuffers(1, &VBOsling);
//	glGenBuffers(1, &EBOsling);
//
//	glBindVertexArray(VAOsling);
//	glBindBuffer(GL_ARRAY_BUFFER, VBOsling);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	//Generating EBO
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOsling);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
//
//	//Enabling the positional floats
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
//		(GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	//Enabling Normal Floats
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
//		(GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//
//	//Enabling the Texture floats
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
//		(GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//
//	//CleanUp (Unbinding)
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//
//
//}
