#pragma once
#include "SDL_image.h"
#include "ECS.h"

class Collision
{
public:
	static bool rectCollision(SDL_Rect entity, SDL_Rect tile);
};