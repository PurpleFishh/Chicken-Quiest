#pragma once
#include <string>
#include "ECS.h"
#include "PositionComponent.h"
#include "SDL_image.h"

class CollisionComponent : public Component
{
private:
	SDL_Texture* texture;

	
	std::string type;
public:
	int col = 0;
	SDL_Rect colliderbox, destRect;
	PositionComponent* posdetails;
	CollisionComponent(std::string type);
	CollisionComponent(int x, int y, int w, int h, std::string type);
	std::string getType();
	void init() override;
	void update() override;
	void draw() override;
};
