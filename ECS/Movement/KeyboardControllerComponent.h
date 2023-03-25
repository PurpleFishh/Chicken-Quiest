#pragma once
#include "../ECS.h"
#include "../../ECS/Movement/PositionComponent.h"
#include "../Visual/SpriteComponent.h"
#include "../Collision/DynamicCollisionComponent.h"

/**
* @class KeyboardControllerComponent
* @brief Handles keyboard input for entity movement
*/
class KeyboardControllerComponent : public Component
{
private:
	/// <summary>
	/// Movement booleans
	/// </summary>
	bool  up = false, down = false, left = false, right = false;
	/// <summary>
	/// Pointer to SpirteComponent of entity(dependency)
	/// </summary>
	SpriteComponent* sprite;
	/// <summary>
	/// Pointer to PositionComponent of entity(dependency)
	/// </summary>
	PositionComponent* position;
	/// <summary>
	/// Pointer to DynamicCollisionComponent of entity(optionaly)
	/// </summary>
	DynamicCollisionComponent* dynamic_col = nullptr;
	
public:
	/// <summary>
	/// If the entity is able to move
	/// </summary>
	bool able_to_move = true;
	
	void init() override;
	/**
	* @brief Handles keyboard input, set the direction of movement, play the needed animation for the activity that the entity is doing
	*/
	void handleEvents() override;
	//void keyevent();
};