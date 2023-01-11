#pragma once
#include "SDL_image.h"
#include "ECS.h"
#include "PositionComponent.h"

class CollisionUtils
{
public:
	static bool point_in_Rect(float x, float y, const PositionComponent& position);
	static bool point_in_Rect(float x, float y, Vector2D position, int width, int height);
};