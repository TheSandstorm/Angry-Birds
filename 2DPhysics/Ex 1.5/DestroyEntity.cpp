#include "DestroyEntity.h"

void DestroyAllTheThings::destroyTheThings(b2Body* bodyToDestroy)
{
	level->getWorld()->DestroyBody(bodyToDestroy);

}
