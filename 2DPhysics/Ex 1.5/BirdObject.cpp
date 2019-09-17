#include "BirdObject.h"


void Bird::Render()
{
}

void Bird::initBird(b2World* _World)
{
	b2BodyDef bodyDef;
	//setting the bird to be a dynamic rigidbody
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0, 20);
	bodyDef.angle = 0;

	b2Body* dynamicBody = _World ->CreateBody(&bodyDef);

	b2PolygonShape birdShape;
	birdShape.SetAsBox(1, 1);

	b2FixtureDef birdFixtureDef;
	birdFixtureDef.shape = &birdShape;
	birdFixtureDef.density = 1;
	dynamicBody->CreateFixture(&birdFixtureDef);

	//DEBUG
	std::cout << "Got through all of the initilisation" << std::endl;

	//possibly render the birds



}
