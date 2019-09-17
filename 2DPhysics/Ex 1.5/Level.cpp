#include "Level.h"

Level::Level()
{
	World = std::make_unique<b2World>(Utility::Gravity);
	ContactListener = new Listener;
	World->SetContactListener(&*ContactListener);
	MeshManager::GetInstance();
}

Level::~Level()
{
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
		ObjectVect.push_back(std::make_shared<Box>(Transform(b2Vec2(400,400), 0.0f, b2Vec2(100.0f,100.0f)), b2_dynamicBody, MeshManager::GetShaderProgram(Shader_Attributes::STANDARD_SHADER), MeshManager::SetTexture(TexturePaths::BlueSquareTexture.data())));
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
}

void Level::Render()
{
	for (unsigned int i = 0; i < ObjectVect.size(); i++)
	{
		ObjectVect[i]->Render();
	}
}

void Level::Process(float DeltaTime, CInputManager* _IM)
{
	//If mouse button press add joint.
	//if released then destory joint.

	//Does a step of the world. Might need to become a fixed update loop instead of where it is now
	World->Step(DeltaTime, 2, 2);
	for (unsigned int i = 0; i < ObjectVect.size(); i++)
	{
		ObjectVect[i]->Process();
	}
	//After all process are done clear forces
	World->ClearForces();
}
