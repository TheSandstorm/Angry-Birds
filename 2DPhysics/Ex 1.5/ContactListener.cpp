#include "ContactListener.h"
#include "Box2D/Box2D.h"
#include "Object.h"
#include "Level.h"
#include <string>
#include <iostream>
#include "DestroyEntity.h"
#include "Level.h"


Level* lev;
Listener::Listener() {

}

Listener::~Listener() {

}

void Listener::BeginContact(b2Contact * contact) 
{
}

void Listener::EndContact(b2Contact * contact) {

}

void Listener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold) {
	if (contact) {
		auto bodyUserDataA = static_cast<ObjectData*>(contact->GetFixtureA()->GetBody()->GetUserData());
		auto bodyUserDataB = static_cast<ObjectData*>(contact->GetFixtureB()->GetBody()->GetUserData());
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();

		//getting the force of the contact
		float force = oldManifold->points[0].normalImpulse;

		//checking force of collisions against glass blocks
		if (force > 0.0011f) {
			if (bodyUserDataA && bodyUserDataB) {
				if (bodyUserDataA->ObjectType == "GlassBlock") {
					std::cout << "Contact Glass\n";
					bodyUserDataA->MarkForDestruction();
				}

				else if (bodyUserDataB->ObjectType == "GlassBlock") {
					std::cout << "Contact Glass\n";
					bodyUserDataB->MarkForDestruction();
				}
			}
		}

		//checking force of collisions against pigs
		if (force > 0.11f) {
			if (bodyUserDataA && bodyUserDataB) {
				if (bodyUserDataA->ObjectType == "Pig") {
					std::cout << "Contact Pig\n";
					bodyUserDataA->MarkForDestruction();
					//lev->getWorld()->DestroyBody(contact->GetFixtureA()->GetBody());
					//lev->ObjectVect.erase(lev->ObjectVect.end());
					//bodyA = nullptr;
					
				}

				else if (bodyUserDataB->ObjectType == "Pig") {
					std::cout << "Contact Pig\n";
					bodyUserDataB->MarkForDestruction();
					//lev->getWorld()->DestroyBody(contact->GetFixtureB()->GetBody());
					//lev->ObjectVect.erase(lev->ObjectVect.end());
					//bodyB = nullptr;
				}
			}
		}
	}
}

void Listener::PostSolve(b2Contact * contact, const b2Manifold * oldManifold) {

}
