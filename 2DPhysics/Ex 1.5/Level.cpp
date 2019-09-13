#include "Level.h"

b2World* Level::World;

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
	delete World;
	World = nullptr;
	delete ContactListener;
	ContactListener = nullptr;
}

void Level::Init(int Level)
{
	//Creates Level based on what level number it is.
}

void Level::Render()
{

}

void Level::Process(float DeltaTime)
{
	//Does a step of the world. Might need to become a fixed update loop instead of where it is now
	World->Step(DeltaTime, 2, 2);
	//After all process are done clear forces
	World->ClearForces();
}
