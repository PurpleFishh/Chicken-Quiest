#pragma once
#include "../ECS.h"
#include "../../ECS/Movement/PositionComponent.h"
#include "../Visual/SpriteComponent.h"
#include "../Collision/DynamicCollisionComponent.h"

class KeyboardControllerComponent : public Component
{
private:
	bool  up = false, down = false, left = false, right = false;
	SpriteComponent* sprite;
	PositionComponent* position;
	DynamicCollisionComponent* dynamic_col = nullptr;
	
public:
	bool able_to_move = true;
	
	void init() override;
	void handleEvents() override;
	//void keyevent();
};