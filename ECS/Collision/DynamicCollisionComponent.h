#pragma once
#include "../ECS.h"
#include "../Movement/PositionComponent.h"
#include "SDL_image.h"

class DynamicCollisionComponent : public Component
{
private:
	PositionComponent* position;
	
	bool verifyTileCollision(float x, float y, const vector<Entity*>& what_is_verified);
	bool borderCollision();

	void solveCollision(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2);
	void enemyHit(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2);
	bool verifyExplosionCollision(const vector<Entity*>& list_of_entities, float x, float y, void(* solveCollision)(Entity* entity));
	void playerWin(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2);

	void SolveCollisionOverlay(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2);
public:
	bool onGround = false, isFalling = false;
	bool collisionXcorner1 = false, collisionXcorner2 = false, collisionYcorner1 = false, collisionYcorner2 = false;

	void init() override;
	void update() override;
	
	void collsionManager(bool onGorundFlagModify, bool CollsionFlagsModify, const vector<Entity*>& what_is_verified,bool (DynamicCollisionComponent::* verifier)(float x, float y, const vector<Entity*>& what_is_verified), void(DynamicCollisionComponent::* solver)(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2));
	bool verifyExplosionCollisionManager(float x, float y);
	bool verifyEntityCollision(float x, float y, const vector<Entity*>& what_is_verified);
};

