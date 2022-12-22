#pragma once
#include "ECS.h"
#include "SpriteComponent.h"
#include "DynamicCollisionComponent.h"

class AiBehaviour : public DynamicCollisionComponent
{
private:
	DynamicCollisionComponent *dynamiccol;
public:
	void init() override;
	void update() override;
};

