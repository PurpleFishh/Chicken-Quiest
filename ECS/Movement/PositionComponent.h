#pragma once
#include "../ECS.h"
#include "../../Utils/Vector2D.h"

/**
* @brief Position component for entities
*/
class PositionComponent : public Component
{
public:
	/// <summary>
	/// Position of the entity and its velocity
	/// </summary>
	Vector2D position, velocity;
	/// <summary>
	/// Sign indicates on which axes the entity moves (0 = does not move) and in which direction (-1 = left, 1 = right)
	/// </summary>
	Vector2D sign = Vector2D(0, 0);
	/// <summary>
	/// Speed and scale of the entity
	/// </summary>
	float speed = 1, scale = 1;
	/// <summary>
	/// Height and width of the entity
	/// </summary>
	int height = TILE_SIZE, width = TILE_SIZE;
	/// <summary>
	/// Indicates if the entity is affected by gravity
	/// </summary>
	bool gravity = false;

	/**
	* @brief Construct a new Position Component object
	*/
	PositionComponent();
	/**
	* @brief Construct a new Position Component object
	* @param scale Scale of the entity
	*/
	PositionComponent(float scale);
	/**
	* @brief Construct a new Position Component object
	* @param x X position of the entity
	* @param y Y position of the entity
	*/
	PositionComponent(float x, float y);
	/**
	* @brief Construct a new Position Component object
	* @param x X position of the entity
	* @param y Y position of the entity
	* @param scale Scale of the entity
	*/
	PositionComponent(float x, float y, float scale);
	/**
	* @brief Construct a new Position Component object
	* @param x X position of the entity
	* @param y Y position of the entity
	* @param h Height of the entity
	* @param w Width of the entity
	*/
	PositionComponent(float x, float y, int h, int w);
	/**
	* @brief Construct a new Position Component object
	* @param x X position of the entity
	* @param y Y position of the entity
	* @param h Height of the entity
	* @param w Width of the entity
	* @param speed Speed of the entity
	* @param scale Scale of the entity
	*/
	PositionComponent(float x, float y, int h, int w, float speed, float scale);
	/**
	* @brief Construct a new Position Component object
	* @param x X position of the entity
	* @param y Y position of the entity
	* @param h Height of the entity
	* @param w Width of the entity
	* @param speed Speed of the entity
	* @param scale Scale of the entity
	* @param gravity Indicates if the entity is affected by gravity
	*/
	PositionComponent(float x, float y, int h, int w, float speed, float scale, bool gravity);

	void init() override;
	void update() override;

	/**
	* @brief Get the Potential Position object calculated by the actual position, velocity and the diraction of movement(sign)
	*/
	Vector2D getPotentialPosition();
	/**
	* @brief Get the Potential Velocity object calculated by the actual velocity and the diraction of movement(sign)
	*/
	Vector2D getPotentialVelocity();
};