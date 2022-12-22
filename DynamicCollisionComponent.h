#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "SDL_image.h"

class DynamicCollisionComponent : public SpriteComponent
{
private:
	bool verifyTileCollision(int x, int y);
	bool borderCollision();
public:
	bool onGround = false, isFalling = false;
	bool collisionXcorner1 = false, collisionXcorner2 = false, collisionYcorner1 = false, collisionYcorner2 = false;

	virtual void setNewPosition();
	void solveCollision(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2);
	
	void init() override;
};

