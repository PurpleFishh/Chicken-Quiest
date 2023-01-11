#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "DynamicCollisionComponent.h"
#include "SpriteComponent.h"

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

