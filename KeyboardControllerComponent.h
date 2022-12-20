#pragma once
#include "ECS.h"
#include "PositionComponent.h"

class KeyboardControllerComponent : public Component
{
private:
	bool up = false, down = false, left = false, right = false;
	
public:
	PositionComponent* position;
	
	void init() override;
	void handleEvents() override;
	//void keyevent();
};