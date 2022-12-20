#include "AiBehaviour.h"


void AiBehaviour::init()
{
	SpriteComponent::init();
	posdetails->sign.x = 1;
	if (entity->hasComponent<DynamicCollisionComponent>())
		dynamiccol = entity->getComponent<DynamicCollisionComponent>();
}

void AiBehaviour::update()
{
	if (!(dynamiccol->collisionYcorner1 && dynamiccol->collisionYcorner2))
	{
		posdetails->sign.x *= -1;
		posdetails->velocity.x *= -1;
		cout << dynamiccol->collisionYcorner1 << ' ' << dynamiccol->collisionYcorner2 << endl;
	}
	else
		if (dynamiccol->collisionX)
			posdetails->sign.x *= -1;
}