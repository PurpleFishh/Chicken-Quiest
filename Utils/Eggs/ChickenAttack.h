#pragma once
#include "../../ECS/ECS.h"

/**
 * @brief A class that manages the egg spawn
*/
class ChickenAttack
{
private:
	/// <summary>
	/// Pointer to the egg entity(because there can only be one egg at a time)
	/// </summary>
	static Entity* egg;
public:
	/**
	 * @brief Sets the egg pointer to the given entity
	 * @param newegg The entity to set the egg pointer to
	*/
	static void setEgg(Entity* newegg) { egg = newegg; }
	/**
	 * @brief Checks if the egg has been spawned
	 * @return True if the egg has been spawned, false otherwise
	*/
	static bool eggSpawned() { return egg != nullptr; }
	/**
	 * @brief Gets the egg pointer
	 * @return The egg pointer
	*/
	static Entity* getEgg() { return egg; }
};