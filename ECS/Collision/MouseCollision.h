#pragma once
#include "../ECS.h"
#include "../Movement/PositionComponent.h"
#include "../Visual/SpriteComponent.h"

/**
* @class MouseCollision
* @brief Checks if the mouse is colliding with the entity(menu buttons)
*/
class MouseCollision : public Component
{
private:
	/// <summary>
	/// Pointer to the PositionComponent (dependency)
	/// </summary>
	PositionComponent* position;
	/// <summary>
	/// Pointer to the SpriteComponent (dependency)
	/// </summary>
	SpriteComponent* sprite;
public:
	void init() override;
	void handleEvents() override;

};

