#pragma once
#include "../ECS.h"
#include "../Movement/PositionComponent.h"
#include "../Collision/DynamicCollisionComponent.h"
#include "../Visual/SpriteComponent.h"

class AiBehaviour : public Component
{
private:
	PositionComponent* position;
	DynamicCollisionComponent* dynamiccol;
	SpriteComponent* sprite;

	int movementDirection;
	void AImovement();
public:
	AiBehaviour(int movementDirection);

	void init() override;
	void update() override;
};

