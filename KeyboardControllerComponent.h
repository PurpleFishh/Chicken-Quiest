#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "DynamicCollisionComponent.h"

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