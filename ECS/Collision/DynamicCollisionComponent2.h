#pragma once
#include "../ECS.h"
#include "../Movement/PositionComponent.h"
#include "SDL_image.h"

/**
* @brief Tests for colloision(igonore)
*/
class DynamicCollisionComponent2 : public Component
{
private:
	PositionComponent* position;

	Entity* verifyTileCollision(float x, float y, const vector<Entity*>& what_is_verified);
	bool borderCollision();
	bool verifyEntityCollision(float x, float y, const vector<Entity*>& what_is_verified);

	void solveCollision(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2);
	void enemyHit(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2);
	bool verifyExplosionCollision(const vector<Entity*>& list_of_entities, float x, float y, void(*solveCollision)(Entity* entity));
	void playerWin(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2);

	void SolveCollisionAI(PositionComponent* collider_pos);
public:
	bool onGround = false, isFalling = false;
	bool collisionXcorner1 = false, collisionXcorner2 = false, collisionYcorner1 = false, collisionYcorner2 = false;

	void init() override;
	void update() override;

	void collsionManager(bool onGorundFlagModify, bool CollsionFlagsModify, const vector<Entity*>& what_is_verified, Entity* (DynamicCollisionComponent2::* verifier)(float x, float y, const vector<Entity*>& what_is_verified), void(DynamicCollisionComponent2::* solver)(PositionComponent *collider_pos));
	bool verifyExplosionCollisionManager(float x, float y);
};

