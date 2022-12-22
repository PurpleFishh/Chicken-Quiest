#include "AiBehaviour.h"


void AiBehaviour::init()
{
	PositionComponent::init();
	sign.x = 1;
	if (entity->hasComponent<DynamicCollisionComponent>())
		dynamiccol = entity->getComponent<DynamicCollisionComponent>();
}

void AiBehaviour::update()
{
	//dynamiccol->setNewPosition();
	//cout << dynamiccol->collisionYcorner2 << endl;
	if (!dynamiccol->collisionYcorner2)
	{
		sign.x *= -1;
		//posdetails->velocity.x *= -1;
		dynamiccol->solveCollision(width, height, false, true, false, false);
		//cout << dynamiccol->collisionYcorner1 << ' ' << dynamiccol->collisionYcorner2 << endl;
	}
	else if (!dynamiccol->collisionYcorner1)
	{
		sign.x = 1;
		//posdetails->velocity.x *= -1;
		//destRect.x = (int)posdetails->position.x;
		//cout << destRect.x << endl;
		dynamiccol->solveCollision(width, height, true, false, false, false);
		//destRect.x = ((int)(destRect.x / 64) + 1) * 64;
		//posdetails->velocity.x = 0;
		//cout << destRect.x << ' ' << posdetails->position << endl;
		//posdetails->position.x = destRect.x;
	}
	else
		if (dynamiccol->collisionXcorner1 || dynamiccol->collisionXcorner2)
		{
			sign.x *= -1;
			velocity.x = 0;
		}
}