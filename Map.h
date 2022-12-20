#pragma once
#include "SDL_image.h"

class Map 
{
public:
	static int rows, cols;
	static void LoadMap(const char* mapPath);
	static void addTile(int srcX, int srcY, int x, int y, SDL_Texture* texture);
};