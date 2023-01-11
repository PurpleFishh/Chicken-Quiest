#pragma once
#include "ECS.h"

class EntitiesDeathManager
{
public:
	static void playerDeath(Entity* entity);
	static void enemyDeath(Entity* entity);

};

