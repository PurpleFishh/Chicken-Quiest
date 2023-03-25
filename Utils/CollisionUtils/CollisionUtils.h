#pragma once
#include "SDL_image.h"
#include "../../ECS/ECS.h"
#include "../../ECS/Movement/PositionComponent.h"

/**
 * @brief CollisionUtils class that contains tools for collision detection
*/
class CollisionUtils
{
public:
	/**
	 * @brief Checks if two SDL_Rects are colliding using AABB method
	 * @param a First SDL_Rect
	 * @param b Second SDL_Rect
	 * @return True if the two SDL_Rects are colliding, false otherwise
	*/
	static bool point_in_Rect(float x, float y, const PositionComponent& position);
	/**
	 * @brief Checks if a point is inside an rectangle
	 * @param x X coordinate of the point
	 * @param y Y coordinate of the point
	 * @param position Vector of the rectangle position
	 * @param width Width of the rectangle
	 * @param height Height of the rectangle
	 * @return True if the point is inside the SDL_Rect, false otherwise
	*/
	static bool point_in_Rect(float x, float y, Vector2D position, int width, int height);
};