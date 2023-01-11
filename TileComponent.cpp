#include "TileComponent.h"
#include "TextureManager.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "Game.h"


TileComponent::TileComponent(int srcX, int srcY, int x, int y, int tilesize, int tilescale, const char* path)
{
	texture = TextureManager::LoadTexture(path);
	scrRect.x = srcX;
	scrRect.y = srcY;
	scrRect.w = scrRect.h = tilesize;

	destRect.x = x;
	destRect.y = y;
	destRect.w = destRect.h =tilesize * tilescale;
}
TileComponent::TileComponent(int srcX, int srcY, int x, int y, int tilesize, int tilescale, SDL_Texture* texture)
{
	this->texture = texture;
	scrRect.x = srcX;
	scrRect.y = srcY;
	scrRect.w = scrRect.h = tilesize;

	destRect.x = x;
	destRect.y = y;
	destRect.w = destRect.h =tilesize * tilescale;
}
TileComponent::TileComponent(int srcX, int srcY, int x, int y, int tilesize, int tilescale, SDL_Texture* texture, bool flip) : TileComponent(srcX, srcY, x, y, tilesize, tilescale, texture)
{
	this->flip = flip;
}


void TileComponent::init()
{
	entity->addCompoent<PositionComponent>((float)destRect.x, (float)destRect.y);
	auto& sprite = entity->addCompoent<SpriteComponent>(texture);
	if (flip)
		sprite.spriteFlip = SDL_FLIP_HORIZONTAL;
}
