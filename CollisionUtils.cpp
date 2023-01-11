#include "CollisionUtils.h"

bool CollisionUtils::point_in_Rect(float x, float y, const PositionComponent& position)
{
	return point_in_Rect(x, y, position.position, position.width, position.height);
}
bool CollisionUtils::point_in_Rect(float x, float y, Vector2D position, int width, int height)
{
	return ((x > position.x && x <position.x + width)
		&& (y > position.y && y < position.y + height));
}