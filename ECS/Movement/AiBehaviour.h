#pragma once
#include "../ECS.h"
#include "../Movement/PositionComponent.h"
#include "../Collision/DynamicCollisionComponent.h"
#include "../Visual/SpriteComponent.h"

/**
* @brief This class is responsible for the movement of the AI(enemy) in the game.
*/
class AiBehaviour : public Component
{
private:
	/// <summary>
	/// Pointer to the PositionComponent (dependency).
	/// </summary>
	PositionComponent* position;
	/// <summary>
	/// Pointer to the DynamicCollisionComponent (dependency).
	/// </summary>
	DynamicCollisionComponent* dynamiccol;
	/// <summary>
	/// Pointer to the SpriteComponent (dependency).
	/// </summary>
	SpriteComponent* sprite;
	/// <summary>
	/// The movement direction of the AI(-1 - moves to left, 1 - moves to right).
	/// </summary>
	int movementDirection;
	/**
	* @brief This method is responsible for the movement of the AI(enemy) in the game.
	*/
	void AImovement();
public:
	/**
	* @brief Constructor of the AiBehaviour class.
	* @param movementDirection The movement direction of the AI(-1 - moves to left, 1 - moves to right).
	*/
	AiBehaviour(int movementDirection);

	void init() override;
	void update() override;
};

