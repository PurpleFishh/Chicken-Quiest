#pragma once
#include "../ECS.h"
#include "../Movement/PositionComponent.h"
#include "../Visual/SpriteComponent.h"

class MouseCollision : public Component
{
private:
	PositionComponent* position;
	SpriteComponent* sprite;
public:
	void init() override;
	void handleEvents() override;

};

