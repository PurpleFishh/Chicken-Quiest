#pragma once
#include "SDL_image.h"
#include "ECS.h"
#include "PositionComponent.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
protected:
	SDL_Texture* texture;
	PositionComponent* posdetails;
public:
	SDL_Rect srcRect;
	SDL_Rect destRect;
	//bool onGround = false;
	SpriteComponent() = default;
	SpriteComponent(const char* textureFile);
	SpriteComponent(SDL_Texture* texture);

	void setTexture(const char* textureFile);
	void setTexture(SDL_Texture* texture);
	virtual void setNewPosition();

	void init() override;
	void update() override;
	void draw() override;
};
