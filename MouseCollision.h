#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"

class MouseCollision : public Component
{
private:
	PositionComponent* position;
	SpriteComponent* sprite;
public:
	void init() override;
	void handleEvents() override;

};

