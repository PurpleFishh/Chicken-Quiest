#pragma once
#include "../../ECS/ECS.h"

/// This class is used to manage the death of entities
class EntitiesDeathManager
{
public:
	/**
	 * @brief This function is used to manage the death of the player
	 * @param entity The entity that has to be managed
	*/
	static void playerDeath(Entity* entity);
	/**
	* @brief This function is used to manage the death of the enemy
	* @param entity The entity that has to be managed
	*/
	static void enemyDeath(Entity* entity);

};

