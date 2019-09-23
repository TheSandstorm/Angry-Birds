#include "Level.h"

ObjectData objdata;

Level::Level()
{
	SlingShotPos = b2Vec2(1.5f, 1.5f);
	World = std::make_unique<b2World>(Utility::Gravity);
	ContactListener = new Listener;
	World->SetContactListener(&*ContactListener);
	MeshManager::GetInstance();
	MouseJoint = nullptr;
	m_nullBody = nullptr;
}

Level::~Level()
{
	ObjectVect.clear();
	BirdVect.clear();
	if (MouseJoint)
	{
		World->DestroyJoint(MouseJoint);
	}
	MeshManager::DestroyInstance();
	World.reset();
	delete ContactListener;
	ContactListener = nullptr;
}

void Level::Init(int Level)
{
	switch (Level)
	{
	case LEVEL_INCORRECT:
	{
		std::wcout << "Level was not Init correctly\n";
		break;
	}
	case LEVELSTATE_1:
	{
		ObjectVect.push_back(std::make_shared<Ground>(Transform(b2Vec2(0.0f, 0.0f), 0.0f, b2Vec2(20.0f, 0.000001f)), b2_staticBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(10.5f, 5.0f), 0.0f, b2Vec2(2.25f, 0.1f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(9.0f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(12.0f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(12.0f, 1.0f), 0.0f, b2Vec2(0.1f, 0.25f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(12.0f, 1.0f), 0.0f, b2Vec2(0.1f, 0.0f)), b2_staticBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		BirdVect.push_back(std::make_shared<Bird>(Transform(b2Vec2(1.8f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::BlueSquareTexture.data())));
		BirdVect.push_back(std::make_shared<Bird>(Transform(b2Vec2(2.4f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::BlueSquareTexture.data())));
		//enemy
		ObjectVect.push_back(std::make_shared<Enemy>(Transform(b2Vec2(9.5f, 0.5f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::WaterTexture.data())));
		break;
	
	}
	case LEVELSTATE_2:
	{
		break;
	}
	default:
		break;
	}
	//Creates Level based on what level number it is.
	for (auto it : ObjectVect) 
	{
		it->Init(World.get());
	}
	//init the birds
	for (auto it : BirdVect)
	{
		it->Init(World.get());
	}
	for (auto it : EnemyVect)
	{
		it->Init(World.get());
	}
	b2BodyDef bodyDef;
	m_nullBody = World->CreateBody(&bodyDef);
}

void Level::Render()
{
	for (unsigned int i = 0; i < ObjectVect.size(); i++)
	{
		ObjectVect[i]->Render();
	}
	for (unsigned int i = 0; i < BirdVect.size(); i++)
	{
		BirdVect[i]->Render();
	}
	for (unsigned int i = 0; i < EnemyVect.size(); i++)
	{
		EnemyVect[i]->Render();
	}
}

void Level::Process(float DeltaTime, CInputManager* _IM)
{
	//If mouse button press add joint.
	//if released then destory joint.

	//Does a step of the world. Might need to become a fixed update loop instead of where it is now
	World->Step(DeltaTime, 10, 10);
	World->ClearForces();


	float MouseX = float(_IM->GetMousePos().x/Utility::Ratio);

	float MouseY = float((Utility::SCR_HEIGHT -_IM->GetMousePos().y)/Utility::Ratio);
	
	std::vector<std::shared_ptr<Object>>::iterator it = ObjectVect.begin();
	while (it != ObjectVect.end()) {
		if ((*it)->Data->IsMarkedForDestruction) {
			it = ObjectVect.erase(it);
			std::cout << "Erased an element. Current Body count:" << World->GetBodyCount() << std::endl;
		}
		else {
			it++;
		};
	}


	#pragma region revoluteJoint


	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = ObjectVect[4]->GetBody();
	revoluteJointDef.bodyB = ObjectVect[5]->GetBody();
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA.Set(1, 1);//the top right corner of the box
	revoluteJointDef.localAnchorB.Set(2, 2);//center of the circle
	b2RevoluteJoint* m_joint = (b2RevoluteJoint*)World->CreateJoint(&revoluteJointDef);

	revoluteJointDef.enableMotor = true;
	revoluteJointDef.maxMotorTorque = 100;
	revoluteJointDef.motorSpeed = 200 * DeltaTime;
	ObjectVect[3]->GetBody()->ApplyAngularImpulse(1, true);
	ObjectVect[3]->GetBody()->ApplyTorque(20, true);

#pragma endregion

	#pragma region revoluteJoint
#pragma endregion

	//Put this into a function
	if (BirdVect.size() != 0)
	{

		b2Body* body = BirdVect.back()->GetBody();

		//Create the mouse joint and initialize it

		if (CInputManager::MouseArray[MOUSE_LEFT] == FIRST_PRESSED && MouseJoint == nullptr) {

			//BirdVect.back()->SetPosition(b2Vec2(MouseX, MouseY));

			body->SetTransform(b2Vec2(MouseX, MouseY), 0.0f);

			body->SetAwake(false);

			MouseDef.bodyA = m_nullBody;

			MouseDef.bodyB = body;

			MouseDef.target = b2Vec2(MouseX, MouseY);

			MouseDef.maxForce = 1000.0f;

			MouseDef.frequencyHz = 100.0f;

			MouseDef.dampingRatio = 6.0f;

			MouseDef.collideConnected = false;

			MouseJoint = static_cast<b2MouseJoint*>(World->CreateJoint(&MouseDef));

			body->SetFixedRotation(true);

		}



		//Move the mouse joint in relation to the mouse pos

		if (CInputManager::MouseArray[MOUSE_LEFT] == HELD && MouseJoint != nullptr) {

			if ((body->GetPosition() - SlingShotPos).Length() >= 1.0f) {

				b2Vec2 d = body->GetPosition() - SlingShotPos;

				d.Normalize();

				d *= 0.99f;

				//BirdVect.back()->SetPosition(d + SlingShotPos);

				body->SetTransform(d + SlingShotPos, 0.0f);				

				MouseJoint->SetTarget(d + SlingShotPos);

			}

			else {

				MouseJoint->SetTarget(b2Vec2(MouseX, MouseY));

				//BirdVect.back()->SetPosition(b2Vec2(MouseX, MouseY));

			}

		}



		//Destroy the mouse joint, calculate the spring force, and apply it

		if (CInputManager::MouseArray[MOUSE_LEFT] == RELEASED && MouseJoint != nullptr) {



			World->DestroyJoint(MouseJoint);

			MouseJoint = nullptr;

			//Using the spring formula, f = -kx for the slingshot

			b2Vec2 Direction = body->GetPosition() - SlingShotPos;

			b2Vec2 Force = Direction;				//Force is a copy of Direction because .Normalize() changes the b2vec2 its used on

			float k = 12.0f;						//Strength of the spring

			float x = Direction.Length();			//Distance stretched

			Force.Normalize();						//Normalizing the direction vector

			Force *= -1.0f * (k * x);				//Calculating the force and multiplying it to the direction vector (F = -1 * (k * x))



			body->SetAwake(false);

			body->SetAwake(true);

			body->SetLinearVelocity(b2Vec2(Force.x, Force.y));

			body->SetFixedRotation(false);

			BirdVect.back()->m_bEnableDecay = true;

			ObjectVect.push_back(BirdVect.back());

			BirdVect.pop_back();

			World->DestroyBody(m_nullBody);

			b2BodyDef bodyDef;

			m_nullBody = World->CreateBody(&bodyDef);

		}

		body = nullptr; //since this is a temp pointer, just making sure that we dont leave an unsafe pointer
	}

}