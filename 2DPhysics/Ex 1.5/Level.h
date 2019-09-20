#pragma once
#include "Utility.h"
#include "InputManger.h"
#include "MeshManager.h"
#include "BoxObject.h"
#include "Object.h"
#include "BirdObject.h"
#include "ContactListener.h"
#include "GroundObject.h"

enum LevelState
{
	LEVEL_INCORRECT,
	LEVELSTATE_1,
	LEVELSTATE_2
};

class Level
{
public:
	Level();
	~Level();

	void Init(int Level);
	void Render();
	void Process(float DeltaTime, CInputManager* _IM);
	
private:



	b2Vec2 SlingShotPos;
	std::vector<std::shared_ptr<Object>> ObjectVect;

	
	Listener* ContactListener;
	std::unique_ptr<b2World> World;

	Bird* birb;
	Ground* floor;
	CInputManager* input;
};
