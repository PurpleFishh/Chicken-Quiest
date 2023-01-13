#include "DynamicCollisionComponent2.h"
#include "../../Layering/Layering.h"
#include "../../Map/Map.h"
#include "../../Game.h"
#include "CollisionComponent.h"
#include "../../Managers/DeathManager/EntitiesDeathManager.h"
#include "../../ElementsConstructors/EntityConstructor.h"
#include "../../ECS/Movement/KeyboardControllerComponent.h"
#include "../../Utils/CollisionUtils/CollisionUtils.h"
#include "../../Managers/ErrorHandler/ErrorHandler.h"


void DynamicCollisionComponent2::init()
{
	if (!entity->hasComponent<PositionComponent>())
		entity->addCompoent<PositionComponent>();
	position = entity->getComponent<PositionComponent>();

	// Gravity
	position->sign.y = 1;
}

void DynamicCollisionComponent2::update()
{
	verifyTileCollision(0, 0, Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerMap));
	//collsionManager(true, true, Layers::getLayer(Layers::layerMap), &DynamicCollisionComponent2::verifyTileCollision, &DynamicCollisionComponent2::SolveCollisionAI);
}

void  DynamicCollisionComponent2::collsionManager(bool onGorundFlagModify, bool CollsionFlagsModify, const vector<Entity*>& what_is_verified, Entity* (DynamicCollisionComponent2::* verifier)(float x, float y, const vector<Entity*>& what_is_verified),
	void (DynamicCollisionComponent2::* solveCollision)(PositionComponent* collider_pos))
{
	if (CollsionFlagsModify)
		collisionXcorner1 = collisionXcorner2 = collisionYcorner1 = collisionYcorner2 = false;

	if (CollsionFlagsModify) borderCollision();
	auto tile = (this->*verifier)(position->position.x, position->position.y + position->height, what_is_verified);
	if (tile != nullptr)
		(this->*solveCollision)(tile->getComponent<PositionComponent>());
	tile = (this->*verifier)(position->position.x + position->width, position->position.y + position->height, what_is_verified);
	if (tile != nullptr)
		(this->*solveCollision)(tile->getComponent<PositionComponent>());
}

void DynamicCollisionComponent2::SolveCollisionAI(PositionComponent* collider_pos)
{

	// Calculate the overlapping area
	int overlap_x = static_cast<int>(std::min(position->position.x + position->width, collider_pos->position.x + collider_pos->width) - std::max(position->position.x, collider_pos->position.x));
	int overlap_y = static_cast<int>(std::min(position->position.y + position->height, collider_pos->position.y + collider_pos->height) - std::max(position->position.y, collider_pos->position.y));

	// Decide which side the collision is happening and move rect1 accordingly
	if (overlap_x < overlap_y) {
		if (position->position.x < collider_pos->position.x) {
			position->position.x -= overlap_x;
		}
		else {
			position->position.x += overlap_x;
		}
	}
	else {
		
		if (position->position.y < collider_pos->position.y) {
			position->position.y -= overlap_y;
		}
		else {
			position->position.y += overlap_y;
		}
	}
}

void DynamicCollisionComponent2::solveCollision(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2)
{
	if (collsioncornerX1)
	{
		//collisionXcorner1 = true;

		position->position.x = static_cast<float>(((int)(position->position.x / tileW) + 1) * tileW);
		position->velocity.x = 0;
	}
	if (collsioncornerX2)
	{
		//collisionXcorner2 = true;

		position->position.x = static_cast<float>(((int)(position->position.x / tileW) + 1) * tileW - position->width);
		position->velocity.x = 0;
	}
	if (collsioncornerY1)
	{
		//collisionYcorner1 = true;

		position->position.y = static_cast<float>(((int)(position->position.y / tileH) + 1) * tileH);
		position->velocity.y = 0;
		// Oprim saltul si aplicam gravitata la loc(il facem sa coboare cand daca cu capul de colziune)
		position->sign.y = 1;
	}
	if (collsioncornerY2)
	{
		// collisionYcorner2 = true;

		position->position.y = static_cast<float>(((int)(position->position.y / tileH) + 1) * tileH - position->height);
		position->velocity.y = 0;
	}
}
void DynamicCollisionComponent2::enemyHit(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2)
{
	for (auto& player : Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerPlayer))
		EntitiesDeathManager::playerDeath(player);
}

Entity* DynamicCollisionComponent2::verifyTileCollision(float x, float y, const vector<Entity*>& what_is_verified)
{
	for(auto tile : what_is_verified)
	{
		if(tile->hasComponent<CollisionComponent>())
		{
			auto tile_pos = tile->getComponent<PositionComponent>();
			bool coll = false;
			if (position->position.x >= tile_pos->position.x && position->position.x < tile_pos->position.x + tile_pos->width && position->position.y >= tile_pos->position.y && position->position.y < tile_pos->position.y + tile_pos->height) {
				coll = true;
			}
			if (position->position.x + position->width > tile_pos->position.x && position->position.x + position->width <= tile_pos->position.x + tile_pos->width && position->position.y >= tile_pos->position.y &&
				position->position.y < tile_pos->position.y + tile_pos->height) {
				coll = true;
			}
			if (position->position.x >= tile_pos->position.x && position->position.x < tile_pos->position.x + tile_pos->width && position->position.y + position->height > tile_pos->position.y &&
				position->position.y + position->height <= tile_pos->position.y + tile_pos->height) {
				coll = true;
			}
			if (position->position.x + position->width > tile_pos->position.x && position->position.x + position->width <= tile_pos->position.x + tile_pos->width && position->position.y + position->height > tile_pos->position.y &&
				position->position.y + position->height <= tile_pos->position.y + tile_pos->height) {
				coll = true;
			}
			if(coll)
				SolveCollisionAI(tile_pos);
		}
	}
	return nullptr;
}

bool DynamicCollisionComponent2::verifyEntityCollision(float x, float y, const vector<Entity*>& what_is_verified)
{
	for (auto& verify_entity : what_is_verified)
	{
		if (verify_entity->hasComponent<CollisionComponent>())
		{
			auto* verify_entityPosition = verify_entity->getComponent<PositionComponent>();
			if (verify_entityPosition->position.x + verify_entityPosition->width > x && verify_entityPosition->position.x < x)
				if (verify_entityPosition->position.y + verify_entityPosition->height > y && verify_entityPosition->position.y < y)
					return true;
		}
	}
	return false;
}

bool DynamicCollisionComponent2::verifyExplosionCollisionManager(float x, float y)
{
	bool collision = verifyExplosionCollision(Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerPlayer), x, y, &EntitiesDeathManager::playerDeath)
		|| verifyExplosionCollision(Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerEnemy), x, y, &EntitiesDeathManager::enemyDeath);
	return collision;
}

bool DynamicCollisionComponent2::verifyExplosionCollision(const vector<Entity*>& list_of_entities, float x, float y, void(*solveCollision)(Entity* entity))
{
	for (auto& checking_entity : list_of_entities)
	{
		if (checking_entity->hasComponent<CollisionComponent>())
		{
			auto* checkingPosition = checking_entity->getComponent<PositionComponent>();
			if ((checkingPosition->position.x > x - EXPLOSION_W / 2 && checkingPosition->position.x < x + EXPLOSION_W / 2)
				&& (checkingPosition->position.y > y - EXPLOSION_H / 2 && checkingPosition->position.y < y + EXPLOSION_H / 2))
			{
				solveCollision(checking_entity);
				continue;
			}
			if ((checkingPosition->position.x + checkingPosition->width > x - EXPLOSION_W / 2 && checkingPosition->position.x + checkingPosition->width < x + EXPLOSION_W / 2)
				&& (checkingPosition->position.y + checkingPosition->height > y - EXPLOSION_H / 2 && checkingPosition->position.y + checkingPosition->height < y + EXPLOSION_H / 2))
			{
				solveCollision(checking_entity);
				continue;
			}
		}
	}
	return false;
}
void DynamicCollisionComponent2::playerWin(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2)
{
	cout << "Player win" << endl;
}

bool  DynamicCollisionComponent2::borderCollision()
{
	if (position->position.x < 0)
	{
		position->position.x = 0;
		position->velocity.x = 0;

		collisionXcorner1 = true;
	}
	if (position->position.y < 0)
	{
		position->position.y = 0;
		position->sign.y = 1;

		collisionYcorner1 = true;
	}
	if (position->position.x + position->width > Map::cols * TILE_SIZE)
	{
		position->position.x = static_cast<float>(Map::cols * TILE_SIZE - position->width);
		position->velocity.x = 0;

		collisionXcorner2 = true;
	}
	if (position->position.y + position->height > Map::rows * TILE_SIZE)
	{
		position->position.y = static_cast<float>(Map::rows * TILE_SIZE - position->height);

		collisionYcorner2 = true;
	}

	return collisionXcorner1 || collisionXcorner2 || collisionYcorner1 || collisionYcorner2;
}