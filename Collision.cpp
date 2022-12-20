#include "Collision.h"

bool Collision::rectCollision(SDL_Rect entity, SDL_Rect tile)
{
	// Verificare daca se intersecteaza
	return (entity.x + entity.w > tile.x && entity.x < tile.x + tile.w)
		&& (entity.y + entity.h > tile.y && entity.y < tile.y + tile.h);
}