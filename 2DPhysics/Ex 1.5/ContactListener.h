#pragma once
#include<Box2D/Box2D.h>
#include "DestroyEntity.h"

//Contact Listener to handle the collisions between objects.
class Listener : public b2ContactListener {
public:
	Listener();
	~Listener();
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2Manifold* oldManifold);

private:

	DestroyAllTheThings* destroyThings;


};