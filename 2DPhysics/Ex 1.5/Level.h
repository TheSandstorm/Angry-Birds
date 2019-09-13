#pragma once
#include "Utility.h"
#include "MeshManager.h"
#include "Object.h"
#include "ContactListener.h"

class Level
{
public:
	Level();
	~Level();

	void Init(int Level);
	void Render();
	void Process(float DeltaTime);
	
private:
	b2Vec2 SlingShotPos;
	std::vector<std::shared_ptr<Object>> ObjectVect;
	
	Listener* ContactListener;
	std::unique_ptr<b2World> World;
};
