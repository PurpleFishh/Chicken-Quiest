#pragma once
#include "../../ECS/ECS.h"
#include "../../ECS/Collision/DynamicCollisionComponent.h"

/**
* @brief EggBoom is a component that is used to destroy the egg after a certain amount of time and kill the entitis in the explosion radius
*/
class EggBoom : public Component
{
private:
	/// <summary>
	/// fps_until_sec is used to count the frames until a second passes
	/// </summary>
	int fps_until_sec = 0;

	/// <summary>
	/// dynamic_col is a pointer to the DynamicCollisionComponent of the entity
	/// </summary>
	DynamicCollisionComponent* dynamic_col;
public:
	/// <summary>
	/// wait_time is the time until the egg explodes in seconds
	/// </summary>
	int wait_time;
	/**
	* @brief Construct a new EggBoom object and set the wait_time
	 * @param wait_time is the time until the egg explodes in seconds
	*/
	EggBoom(int wait_time);
	
	/**
	 * @brief The intialization of the EggBoom component
	*/
	void init() override;
	/**
	 * @brief The update of the EggBoom component
	*/
	void update() override;

};

