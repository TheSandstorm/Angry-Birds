#include "Level.h"
#include "ProgramManager.h"

ObjectData objdata;

bool playerWins = false;
bool playerloses = false;
int count = 0;
int level;

Level::Level()
{
	playerloses = false;
	playerWins = false;
	count = 0;
	//setting the position of the slingshot
	SlingShotPos = b2Vec2(1.5f, 1.5f);
	//initing gravity
	World = std::make_unique<b2World>(Utility::Gravity);
	//create the contact listener for collision checking
	ContactListener = new Listener;
	World->SetContactListener(&*ContactListener);
	//get the meshmanager
	MeshManager::GetInstance();
	//set MouseJoint to nullptr so it can be activated later
	MouseJoint = nullptr;
	//create a null body which can be used as a grounding agent for the mousejoint
	m_nullBody = nullptr;
}

Level::~Level()
{
	//destroy the object vector
	ObjectVect.clear();
	//destroy the bird vector
	BirdVect.clear();
	//if the mouse joint isn't nullptr destroy it
	if (MouseJoint)
	{
		World->DestroyJoint(MouseJoint);
	}
	//destroy the instatnce of the meshmanager
	MeshManager::DestroyInstance();
	//destroy the world
	World.reset();
	//remove the contact listener and set it to nullptr
	delete ContactListener;
	ContactListener = nullptr;
}

//init the level based on which level is passed to the function
void Level::Init(int Level)
{
	//based on what level it is
	switch (Level)
	{
		//in case there is a level that is not on the list
	case LEVEL_INCORRECT:
	{
		std::wcout << "Level was not Init correctly\n";
		break;
	}
	//level 1s
	case LEVELSTATE_1:
	{
		level = 1;

#pragma region pushing to vectors
		//ground
		ObjectVect.push_back(std::make_shared<Ground>(Transform(b2Vec2(0.0f, 0.0f), 0.0f, b2Vec2(20.0f, 0.000001f)), b2_staticBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));

		//indestructible blocks
		//push a box to the object vector, with transform, scale, body type, shadertype and texture
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(10.5f, 3.0f), 0.0f, b2Vec2(2.25f, 0.1f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(12.0f, 3.5f), 0.0f, b2Vec2(0.1f, 0.25f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(10.5f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(9.0f, 3.5f), 0.0f, b2Vec2(0.1f, 0.25f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(10.5f, 4.3f), 0.0f, b2Vec2(2.25f, 0.1f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		
		
		//glass blocks
		//push a glass box to the object vector, with transform, scale, body type, shadertype and texture
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(5.0f, 4.3f), 0.0f, b2Vec2(0.1f, 0.1f)), b2_staticBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(5.0f, 4.3f), 0.0f, b2Vec2(1.5f, 0.1f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Glass>(Transform(b2Vec2(9.0f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::GlassTexture.data())));
		ObjectVect.push_back(std::make_shared<Glass>(Transform(b2Vec2(12.0f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::GlassTexture.data())));
		ObjectVect.push_back(std::make_shared<Glass>(Transform(b2Vec2(10.0f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::GlassTexture.data())));
		ObjectVect.push_back(std::make_shared<Glass>(Transform(b2Vec2(11.0f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::GlassTexture.data())));

		//birds
		//push a bird to the object vector, with transform, scale, body type, shadertype and texture
		BirdVect.push_back(std::make_shared<Bird>(Transform(b2Vec2(1.8f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::BlueSquareTexture.data())));
		BirdVect.push_back(std::make_shared<Bird>(Transform(b2Vec2(2.4f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::BlueSquareTexture.data())));
		BirdVect.push_back(std::make_shared<Bird>(Transform(b2Vec2(1.4f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::BlueSquareTexture.data())));
		
		//enemies
		//push an enemy to the object vector, with transform, scale, body type, shadertype and texture
		ObjectVect.push_back(std::make_shared<Enemy>(Transform(b2Vec2(9.5f, 0.5f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::WaterTexture.data())));
		ObjectVect.push_back(std::make_shared<Enemy>(Transform(b2Vec2(9.5f, 3.3f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::WaterTexture.data())));
		ObjectVect.push_back(std::make_shared<Enemy>(Transform(b2Vec2(9.5f, 4.5f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::WaterTexture.data())));
		break;
#pragma endregion
	
	}
	case LEVELSTATE_2:
	{
		level = 2;
#pragma region pushing to vectors
		//ground
		ObjectVect.push_back(std::make_shared<Ground>(Transform(b2Vec2(0.0f, 0.0f), 0.0f, b2Vec2(20.0f, 0.000001f)), b2_staticBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));

		//indestructible blocks
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(10.5f, 3.0f), 0.0f, b2Vec2(2.25f, 0.1f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(12.0f, 3.5f), 0.0f, b2Vec2(0.1f, 0.25f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(10.5f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(9.0f, 3.5f), 0.0f, b2Vec2(0.1f, 0.25f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(10.5f, 4.3f), 0.0f, b2Vec2(2.25f, 0.1f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(11.0f, 4.3f), 0.0f, b2Vec2(0.1f, 0.1f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(10.5f, 4.3f), 0.0f, b2Vec2(0.1f, 0.1f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(10.0f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(11.0f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::TestTexture.data())));

		//glass blocks
		ObjectVect.push_back(std::make_shared<Glass>(Transform(b2Vec2(9.0f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::GlassTexture.data())));
		ObjectVect.push_back(std::make_shared<Glass>(Transform(b2Vec2(12.0f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::GlassTexture.data())));

		//birds
		BirdVect.push_back(std::make_shared<Bird>(Transform(b2Vec2(1.8f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::BlueSquareTexture.data())));
		BirdVect.push_back(std::make_shared<Bird>(Transform(b2Vec2(2.4f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::BlueSquareTexture.data())));
		BirdVect.push_back(std::make_shared<Bird>(Transform(b2Vec2(1.4f, 1.0f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::BlueSquareTexture.data())));

		//enemies
		ObjectVect.push_back(std::make_shared<Enemy>(Transform(b2Vec2(9.5f, 0.5f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::WaterTexture.data())));
		ObjectVect.push_back(std::make_shared<Enemy>(Transform(b2Vec2(9.5f, 3.3f), 0.0f, b2Vec2(0.1f, 0.5f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::WaterTexture.data())));
#pragma endregion
		break;
	}
	default:
		break;
	}
	//init the walls and enemies
	for (auto it : ObjectVect) 
	{
		it->Init(World.get());
	}
	//init the birds
	for (auto it : BirdVect)
	{
		it->Init(World.get());
	}
	//give the null body an actual reference in the box2d world
	b2BodyDef bodyDef;
	m_nullBody = World->CreateBody(&bodyDef);
}

void Level::Render()
{
	//render the walls and enemies
	for (unsigned int i = 0; i < ObjectVect.size(); i++)
	{
		ObjectVect[i]->Render();
	}
	//render the birds
	for (unsigned int i = 0; i < BirdVect.size(); i++)
	{
		BirdVect[i]->Render();
	}
}

void Level::Process(float DeltaTime, CInputManager* _IM){

	//Does a step of the world
	World->Step(DeltaTime, 10, 10);
	//clear the forces on the world
	World->ClearForces();

	//get mouse x position
	float MouseX = float(_IM->GetMousePos().x/Utility::Ratio);
	//get mouse y position
	float MouseY = float((Utility::SCR_HEIGHT -_IM->GetMousePos().y)/Utility::Ratio);
	//iterate through the object vector
	std::vector<std::shared_ptr<Object>>::iterator it = ObjectVect.begin();
	while (it != ObjectVect.end()) {
		//if the tag is pig add to the count as there are still pigs in the level
		if ((*it)->Data->ObjectType == "Pig") {
			count++;
		}
		//check to see if something is marked for destruction
		if ((*it)->Data->IsMarkedForDestruction) {
			//if the object is marked then remove it the base class destructor is invoked
			it = ObjectVect.erase(it);
			//log it in the console
			std::cout << "Erased an element. Current Body count:" << World->GetBodyCount() << std::endl;
		}
		//if the item is not marked then increment the iterator
		else {
			it++;
		};
	}

#pragma region wincon
	//checks to see if there are no birds in the bird vector and there are still pigs
	if (BirdVect.size() == 0 && count >= 1) {
		playerloses = true;
	}
	//reset the count if there is at least one pig left
	if (count >= 1) {
		count = 0;
	}
	//otherwise the player wins
	else {
		playerWins = true;
	}
	//player lose if statement
	if (playerloses) {
		std::cout << "Player Loses" << std::endl;
	}
	//player wins if statement 
	if (playerWins) {
		playerloses = false;
		std::cout << "Player Wins" << std::endl;
	}
#pragma endregion


#pragma region revoluteJoint

	//create the definition of the revolute joint
	b2RevoluteJointDef revoluteJointDef;
	//assign the bodies
	revoluteJointDef.bodyA = ObjectVect[6]->GetBody();
	revoluteJointDef.bodyB = ObjectVect[7]->GetBody();
	//make it so they don't collide
	revoluteJointDef.collideConnected = false;
	//set the anchor points about which the bodies will rotate
	revoluteJointDef.localAnchorA.Set(1, 1);//the top right corner of the box
	revoluteJointDef.localAnchorB.Set(2, 2);//center of the circle
	//add the joint to the world
	b2RevoluteJoint* m_joint = (b2RevoluteJoint*)World->CreateJoint(&revoluteJointDef);
	//enable the motor so one of the objects can rotate
	revoluteJointDef.enableMotor = true;
	//set the max torque
	revoluteJointDef.maxMotorTorque = 100;
	//give the motor a speed
	revoluteJointDef.motorSpeed = 20 * DeltaTime;

#pragma endregion


	//if there are still birds in the bird vector
	if (BirdVect.size() != 0)
	{
		//get the last bird in the vector
		b2Body* body = BirdVect.back()->GetBody();

		//Create the mouse joint and initialize it

		//if the user presses the left mouse button and there is currently not a mouse joint
		if (CInputManager::MouseArray[MOUSE_LEFT] == FIRST_PRESSED && MouseJoint == nullptr) {

			//set the transform of the bird to the mouse coords
			body->SetTransform(b2Vec2(MouseX, MouseY), 0.0f);
			//make it so the body is not awake
			body->SetAwake(false);
			//set the body to the nullbody(grounding body)
			MouseDef.bodyA = m_nullBody;
			//body b to the bird
			MouseDef.bodyB = body;
			//make the target the mouse position
			MouseDef.target = b2Vec2(MouseX, MouseY);
			//set up a max force
			MouseDef.maxForce = 1000.0f;
			MouseDef.frequencyHz = 100.0f;
			MouseDef.dampingRatio = 6.0f;
			//make it so the mouse cannot collide with the bird
			MouseDef.collideConnected = false;
			//add the joint into the world
			MouseJoint = static_cast<b2MouseJoint*>(World->CreateJoint(&MouseDef));
			//make it so the bird has a fixed rotation
			body->SetFixedRotation(true);

		}


		//if the user is holding the left mouse button and the mouse joint is not a nullptr
		//Move the mouse joint in relation to the mouse pos
		if (CInputManager::MouseArray[MOUSE_LEFT] == HELD && MouseJoint != nullptr) {
			//if the position of the bird - the slingshot position
			//if it is out of the slingshot bounds
			if ((body->GetPosition() - SlingShotPos).Length() >= 1.0f) {
				//get the distance between the bird and the slingshot
				b2Vec2 d = body->GetPosition() - SlingShotPos;
				//normalize it
				d.Normalize();
				//multiply the distance by .99
				d *= 0.99f;
				//set the birds transform to the distance + slingshot position
				body->SetTransform(d + SlingShotPos, 0.0f);				
				//set the mousejoints target to d + slingshot position
				MouseJoint->SetTarget(d + SlingShotPos);

			}
			
			else {
				//make the mouse joint target the mouse position
				MouseJoint->SetTarget(b2Vec2(MouseX, MouseY));
			}

		}


		//if the user releases the mouse and there is a mousejoint
		//Destroy the mouse joint, calculate the spring force, and apply it
		if (CInputManager::MouseArray[MOUSE_LEFT] == RELEASED && MouseJoint != nullptr) {
			//destroy the mousejoint from the box2d world
			World->DestroyJoint(MouseJoint);
			//set the mouseJoint to a nullptr so it can be created again
			MouseJoint = nullptr;

			//Using the spring formula, f = -kx for the slingshot

			b2Vec2 Direction = body->GetPosition() - SlingShotPos;

			b2Vec2 Force = Direction;				//Force is a copy of Direction because .Normalize() changes the b2vec2 its used on

			float k = 12.0f;						//Strength of the spring

			float x = Direction.Length();			//Distance stretched

			Force.Normalize();						//Normalizing the direction vector

			Force *= -1.0f * (k * x);				//Calculating the force and multiplying it to the direction vector (F = -1 * (k * x))



			body->SetAwake(false);
			//set the bird to awake so it can move
			body->SetAwake(true);
			//set the linear velocity
			body->SetLinearVelocity(b2Vec2(Force.x, Force.y));
			//disable the fixed rotation so it can rotate around
			body->SetFixedRotation(false);
			//enable decay so the bird will eventually destroy itself
			BirdVect.back()->m_bEnableDecay = true;
			//push the bird to the back of the object vector
			ObjectVect.push_back(BirdVect.back());
			//remove the bird from the bird vector
			BirdVect.pop_back();
			//destroy the null body as it is no longer needed
			World->DestroyBody(m_nullBody);
			//create a new body def for the null body as it will throw an error as it doesn't exsist when the new mous joint is created
			b2BodyDef bodyDef;
			//add the null body to the worl d
			m_nullBody = World->CreateBody(&bodyDef);

		}

		body = nullptr; //since this is a temp pointer, just making sure that we dont leave an unsafe pointer
	}

}