#pragma once
#include "Utility.h"
#include "InputManger.h"
#include "MeshManager.h"
#include "BirdObject.h"
#include "BoxObject.h"
#include "GroundObject.h"
#include "Object.h"
#include "GlassObject.h"
#include "BirdObject.h"
#include "ContactListener.h"
#include "GroundObject.h"
#include "Enemy.h"

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

	std::unique_ptr<b2World> World;

	b2World* getWorld() { 
		b2World* world = World.get();
		return world; };

	void destroyStuff(b2Body* body);

	std::vector<std::shared_ptr<Object>> ObjectVect;
	std::vector<std::shared_ptr<Bird>> BirdVect;
	std::vector<std::shared_ptr<Enemy>> EnemyVect;



private:
	b2Body* m_nullBody;

	b2Vec2 SlingShotPos;
	

	Listener* ContactListener;
	b2MouseJoint* MouseJoint;
	b2MouseJointDef MouseDef;



	Bird* birb;
	Ground* floor;
	CInputManager* input;
};



