#pragma once
#include "../../ECS/ECS.h"

class ChickenAttack
{
private:
	static Entity* egg;
public:
	static void setEgg(Entity* newegg) { egg = newegg; }
	static bool eggSpawned() { return egg != nullptr; }
	static Entity* getEgg() { return egg; }
};