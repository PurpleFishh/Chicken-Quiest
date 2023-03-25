#pragma once
#include <string>
#include "../ECS.h"
#include "../Visual/SpriteComponent.h"

/**
* @brief Used for entitis that will have collider box
*/
class CollisionComponent : public Component
{
private:
	/// <summary>
	/// Pointer to SpriteComponent (dependecy)
	/// </summary>
	SpriteComponent* sprite;
	
	/// <summary>
	/// An identifier for the collider
	/// </summary>
	std::string type;
public:
	/**
	* @brief Constructor
	* @param type the collider identifier
	*/
	CollisionComponent(std::string type);
	
	/**
	* @brief Returns the collider identifier
	* @return the collider identifier
	*/
	std::string getType();
	void init() override;
	void draw() override;
};
