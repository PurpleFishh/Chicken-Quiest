#pragma once
#include <string>
#include "ECS.h"
#include "SpriteComponent.h"

class CollisionComponent : public Component
{
private:
	SpriteComponent* sprite;
	
	std::string type;
public:
	CollisionComponent(std::string type);
	
	std::string getType();
	void init() override;
	void draw() override;
};
