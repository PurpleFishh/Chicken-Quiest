#pragma once
#include "../ECS/ECS.h"
#include "../Utils/Vector2D.h"
#include "SDL_ttf.h"

class EntityConstructor
{
private:
public:
	static Vector2D player_spawn_position, golden_egg_spawn_position;
	
	static Entity& emptyTile;
	static Entity& spawnPlayer(const Vector2D& spawn_position);
	static Entity& spawnEnemy(const Vector2D& spawn_position);
	static Entity& spawnEgg(const Vector2D& spawn_position);
	static Entity& spawnGoldenEgg(const Vector2D& spawn_position);
	static Entity& spawnExplosion(const Vector2D& spawn_position);
	static Entity& spawnBackground(int scen, int layer, const Vector2D& spawn_position, SDL_Texture* texture, int w, int h, int scrw, int scrh);
	static Entity& spawnText(const Vector2D& spawn_position, std::string text);
	static Entity& spawnInfoBar(int scen, int layer, const Vector2D& spawn_position, SDL_Color color, const std::string& facilities);

	static void AnimationAfter_destroyEntity(Entity* entity);
	static void AnimationAfter_playerWin(Entity* entity);
};

