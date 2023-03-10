#pragma once

#include "../ECS.h"
#include "SDL_image.h"

class TileComponent : public Component
{
private:
	SDL_Rect scrRect, destRect;
	SDL_Texture* texture;
	bool flip = false;
public:
	TileComponent(int srcX, int srcY, int x, int y, int tilesize, int tilescale, const char* path);
	TileComponent(int srcX, int srcY, int x, int y, int tilesize, int tilescale, SDL_Texture* texture);
	TileComponent(int srcX, int srcY, int x, int y, int tilesize, int tilescale, SDL_Texture* texture, bool flip);
	
	void init() override;

};