#pragma once
#include "ECS.h"
#include "DynamicCollisionComponent.h"

class EggBoom : public Component
{
private:
	int fps_until_sec = 0;

	DynamicCollisionComponent* dynamic_col;
public:
	int wait_time;
	EggBoom(int wait_time);
	
	void init() override;
	void update() override;

};

