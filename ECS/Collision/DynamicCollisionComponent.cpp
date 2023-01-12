#include "DynamicCollisionComponent.h"
#include "../../Layering/Layering.h"
#include "../../Map/Map.h"
#include "../../Game.h"
#include "CollisionComponent.h"
#include "../../Managers/DeathManager/EntitiesDeathManager.h"
#include "../../ElementsConstructors/EntityConstructor.h"
#include "../../ECS/Movement/KeyboardControllerComponent.h"
#include "../../Utils/CollisionUtils/CollisionUtils.h"
#include "../../Managers/ErrorHandler/ErrorHandler.h"


void DynamicCollisionComponent::init()
{
	try {
		position = entity->getComponent<PositionComponent>();
		if (!entity->hasComponent<PositionComponent>())		throw ErrorHandler(typeid(DynamicCollisionComponent).name(), typeid(PositionComponent).name());
	}
	catch (ErrorHandler e) { position = &entity->addCompoent<PositionComponent>(); }
	catch (std::exception& ex) { cout << ex.what() << endl; }

	// Gravity
	position->sign.y = 1;
}

void DynamicCollisionComponent::update()
{
	collsionManager(true, true, Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerMap), &DynamicCollisionComponent::verifyTileCollision, &DynamicCollisionComponent::solveCollision);
	if (entity->getLayer_Id() == (int)Layers::game_layers::layerEnemy)
		collsionManager(false, false, Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerPlayer), &DynamicCollisionComponent::verifyEntityCollision, &DynamicCollisionComponent::enemyHit);
	if (entity->getLayer_Id() == (int)Layers::game_layers::layerPlayer)
		collsionManager(false, false, Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerGoldenEggs), &DynamicCollisionComponent::verifyEntityCollision, &DynamicCollisionComponent::playerWin);
}

void  DynamicCollisionComponent::collsionManager(bool onGroundFlagModify, bool CollsionFlagsModify, const vector<Entity*>& what_is_verified, bool (DynamicCollisionComponent::* verifier)(float x, float y, const vector<Entity*>& what_is_verified),
	void (DynamicCollisionComponent::* solveCollision)(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2))
{
	if (CollsionFlagsModify)
		collisionXcorner1 = collisionXcorner2 = collisionYcorner1 = collisionYcorner2 = false;

	if (CollsionFlagsModify) borderCollision();

	// BugFix: - Daca playerul era in cadere, se misca pe axa X si cadea intre doua tile-uri acesta era teleportat la marginea tile-ului din spate
	//		   - Folosim colX pentru a semnala daca a avut loc o coliziune pe axa X(folosim verificarea pentru coloziunile din cadere de exemplu de un perete)
	//         - Folosim in colziunea pe Y colX sa vedem daca colziunea a fost rezolvata cu ajutorul lui X sa nu ii mai schimbam pozitia dubios la player
	//         - Si apoi in final verificam iar coloziunea pe X pentru ca coloziunea cand acesta este pe o platforma(onGround)
	if (position->velocity.x < 0)
	{
		// Alt Doamne fereste...

		// Verificam coliziuni pentru mers in stanga
		// Verificam daca exisata coliziunea in coltul din stanga sus si stanga jos al entitatii
		if ((this->*verifier)(position->position.x, position->position.y + 7, what_is_verified) || (this->*verifier)(position->position.x, position->position.y + position->height - 7, what_is_verified))
			if (!(this->*verifier)(position->position.x + position->width - 1, position->position.y + position->height + 2, what_is_verified))
				if (!(this->*verifier)(position->position.x + position->width, position->position.y, what_is_verified))
				{
					// Daca entitatea e in cadere
					if (!onGround)
					{
						(this->*solveCollision)(TILE_SIZE, TILE_SIZE, true, false, false, false);
						if (CollsionFlagsModify)
							collisionXcorner1 = true;
						//cout << "coll x1" << endl;
					}
				}
	}
	else
		if (position->velocity.x != 0)
		{
			// Verificam coliziuni pentru mers in dreapta
			// Verificam daca exisata coliziunea in coltul din dreapta sus si dreapta jos al entitatii
			if ((this->*verifier)(position->position.x + position->width, position->position.y + 7, what_is_verified) || (this->*verifier)(position->position.x + position->width, position->position.y + position->height - 2, what_is_verified))
				if (!(this->*verifier)(position->position.x + 1, position->position.y + position->height, what_is_verified))
					if (!(this->*verifier)(position->position.x, position->position.y, what_is_verified))
					{
						// Daca entitatea e in cadere
						if (!onGround)
						{
							(this->*solveCollision)(TILE_SIZE, TILE_SIZE, false, true, false, false);
							if (CollsionFlagsModify)
								collisionXcorner2 = true;

							//cout << "coll x2" << endl;
						}
					}
		}
	if (onGroundFlagModify)
		onGround = false;
	// Verificam coliziuni pe y
	if (position->velocity.y < 0)
	{
		// Verificam coliziuni pentru mers in sus
		// Verificam daca exisata coliziunea in coltul din stanga sus si dreapta sus al entitatii
		if ((this->*verifier)(position->position.x, position->position.y, what_is_verified) || (this->*verifier)(position->position.x + position->width - 1, position->position.y, what_is_verified))
		{
			//cout << "Coll y\n";
			// Daca a avut loc coliziune pe X il lasam in pace
			if (!CollsionFlagsModify || !(collisionXcorner1 && collisionXcorner2))
			{
				(this->*solveCollision)(TILE_SIZE, TILE_SIZE, false, false, true, false);
				if (CollsionFlagsModify)
				{
					collisionYcorner1 = (this->*verifier)(position->position.x, position->position.y, what_is_verified);
					collisionYcorner2 = (this->*verifier)(position->position.x + position->width - 1, position->position.y, what_is_verified);
				}
				//cout << "coll y1" << endl;
			}
		}
	}
	else
		if (position->velocity.y != 0)
		{
			// Verificam coliziuni pentru mers in jos
			// Verificam daca exisata coliziunea in coltul din stanga jos si dreapta jos al entitatii
			if ((this->*verifier)(position->position.x + 1, position->position.y + position->height, what_is_verified) || (this->*verifier)(position->position.x + position->width - 1, position->position.y + position->height, what_is_verified))
			{
				//cout << "Coll y\n";
				// Daca a avut loc coliziune pe X il lasam in pace
				if (!CollsionFlagsModify || !(collisionXcorner1 && collisionXcorner2))
				{

					(this->*solveCollision)(TILE_SIZE, TILE_SIZE, false, false, false, true);
					if (CollsionFlagsModify)
					{
						collisionYcorner1 = (this->*verifier)(position->position.x + 2, position->position.y + position->height, what_is_verified);
						collisionYcorner2 = (this->*verifier)(position->position.x + position->width - 2, position->position.y + position->height, what_is_verified);
					}
				}
				//cout << "coll y2" << endl;
				if (onGroundFlagModify)
					onGround = true;
			}
		}

	// Verificam coliziuni pe x
	if (position->velocity.x < 0)
	{
		// Verificam coliziuni pentru mers in stanga
		// Verificam daca exisata coliziunea in coltul din stanga sus si stanga jos al entitatii
		if ((this->*verifier)(position->position.x, position->position.y + 1, what_is_verified) || (this->*verifier)(position->position.x, position->position.y - 1 + position->height, what_is_verified))
		{
			// Verificam cand e deja pe pamant cu aceasta informatie actualizata deja mai sus
			if (onGround)
			{
				(this->*solveCollision)(TILE_SIZE, TILE_SIZE, true, false, false, false);
				if (CollsionFlagsModify)
					collisionXcorner1 = true;
				//cout << "coll x1" << endl;
			}
		}
	}
	else
		if (position->velocity.x != 0)
		{
			// Verificam coliziuni pentru mers in dreapta
			// Verificam daca exisata coliziunea in coltul din dreapta sus si dreapta jos al entitatii
			if ((this->*verifier)(position->position.x + position->width, position->position.y + 1, what_is_verified) || (this->*verifier)(position->position.x + position->width, position->position.y - 1 + position->height, what_is_verified))
			{
				// Verificam cand e deja pe pamant cu aceasta informatie actualizata deja mai sus
				if (onGround)
				{
					(this->*solveCollision)(TILE_SIZE, TILE_SIZE, false, true, false, false);
					if (CollsionFlagsModify)
						collisionXcorner2 = true;
					//cout << "coll x2" << endl;
				}
			}
		}
}

void DynamicCollisionComponent::SolveCollisionOverlay(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2)
{

	// Calculate the overlapping area
	auto pos = Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerGoldenEggs).at(0)->getComponent<PositionComponent>();
	int overlap_x = std::min(position->position.x + position->width, pos->position.x + pos->width) - std::max(position->position.x, pos->position.x);
	int overlap_y = std::min(position->position.y + position->height, pos->position.y + pos->height) - std::max(position->position.y, pos->position.y);

	// Decide which side the collision is happening and move rect1 accordingly
	if (overlap_x > overlap_y) {
		if (position->position.y < pos->position.y) {
			position->position.y -= overlap_y;
		}
		else {
			position->position.y += overlap_y;
		}
	}
	else {
		if (position->position.x < pos->position.x) {
			position->position.x -= overlap_x;
		}
		else {
			position->position.x += overlap_x;
		}
	}
}

void DynamicCollisionComponent::solveCollision(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2)
{
	if (collsioncornerX1)
	{
		position->position.x = static_cast<float>(((int)(position->position.x / tileW) + 1) * tileW);
		position->velocity.x = 0;
	}
	if (collsioncornerX2)
	{
		position->position.x = static_cast<float>(((int)(position->position.x / tileW) + 1) * tileW - position->width);
		position->velocity.x = 0;
	}
	if (collsioncornerY1)
	{
		position->position.y = static_cast<float>(((int)(position->position.y / tileH) + 1) * tileH);
		position->velocity.y = 0;
		// Oprim saltul si aplicam gravitata la loc(il facem sa coboare cand daca cu capul de colziune)
		position->sign.y = 1;
	}
	if (collsioncornerY2)
	{
		position->position.y = static_cast<float>(((int)(position->position.y / tileH) + 1) * tileH - position->height);
		position->velocity.y = 0;
	}
}
bool DynamicCollisionComponent::verifyTileCollision(float x, float y, const vector<Entity*>& what_is_verified)
{
	return what_is_verified[(int)(y / TILE_SIZE) * Map::cols + (int)(x / TILE_SIZE)]->hasComponent<CollisionComponent>();
}

bool DynamicCollisionComponent::verifyEntityCollision(float x, float y, const vector<Entity*>& what_is_verified)
{
	for (auto& verify_entity : what_is_verified)
	{
		if (verify_entity->hasComponent<CollisionComponent>())
		{
			auto* verify_entityPosition = verify_entity->getComponent<PositionComponent>();
			if (CollisionUtils::point_in_Rect(x, y, *verify_entityPosition))
				return true;
			if (position->velocity.x < 0)
			{
				if (CollisionUtils::point_in_Rect(x + position->width, y, *verify_entityPosition))
					return true;
			}
			else if (position->velocity.x > 0)
				if (CollisionUtils::point_in_Rect(x - position->width, y, *verify_entityPosition))
					return true;
		}
	}
	return false;
}

bool DynamicCollisionComponent::verifyExplosionCollision(const vector<Entity*>& list_of_entities, float x, float y, void(*solveCollision)(Entity* entity))
{
	for (auto& checking_entity : list_of_entities)
	{
		if (checking_entity->hasComponent<CollisionComponent>())
		{
			auto* checkingPosition = checking_entity->getComponent<PositionComponent>();
			if(CollisionUtils::point_in_Rect(checkingPosition->position.x, checkingPosition->position.y, Vector2D(x, y), EXPLOSION_W / 2, EXPLOSION_H / 2))
			{
				solveCollision(checking_entity);
				continue;
			}
			if (CollisionUtils::point_in_Rect(checkingPosition->position.x + checkingPosition->width, checkingPosition->position.y + checkingPosition->height, Vector2D(x, y), EXPLOSION_W / 2, EXPLOSION_H / 2))
			{
				solveCollision(checking_entity);
				continue;
			}
		}
	}
	return false;
}

bool  DynamicCollisionComponent::borderCollision()
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
bool DynamicCollisionComponent::verifyExplosionCollisionManager(float x, float y)
{
	bool collision = verifyExplosionCollision(Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerPlayer), x, y, &EntitiesDeathManager::playerDeath)
		|| verifyExplosionCollision(Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerEnemy), x, y, &EntitiesDeathManager::enemyDeath);
	return collision;
}

void DynamicCollisionComponent::playerWin(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2)
{
	entity->getComponent<KeyboardControllerComponent>()->able_to_move = false;
	position->velocity.x = 0;
	position->sign.x = 0;
	EntityConstructor::PlayerWon = true;
}
void DynamicCollisionComponent::enemyHit(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2)
{
	for (auto& player : Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerPlayer))
		EntitiesDeathManager::playerDeath(player);
}