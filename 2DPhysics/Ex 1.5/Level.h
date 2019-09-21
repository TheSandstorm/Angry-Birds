#pragma once
#include "Utility.h"
#include "InputManger.h"
#include "MeshManager.h"
#include "BirdObject.h"
#include "BoxObject.h"
#include "GroundObject.h"
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
	b2Body* m_nullBody;

	b2Vec2 SlingShotPos;
	std::vector<std::shared_ptr<Object>> ObjectVect;
	std::vector<std::shared_ptr<Bird>> BirdVect;
	
	b2MouseJoint* MouseJoint;
	b2MouseJointDef MouseDef;
	Listener* ContactListener;
	std::unique_ptr<b2World> World;

	Bird* birb;
	Ground* floor;
	CInputManager* input;
};
