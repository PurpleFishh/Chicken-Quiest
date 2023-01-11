#pragma once
#include "SDL_image.h"
#include <string>

class Map 
{
private:
	static std::string loaded_mapPath;
public:
	static int rows, cols, difficulty;

	static void LoadMap(std::string mapPath);
	static void addTile(int srcX, int srcY, int x, int y, SDL_Texture* texture);
	static void addTile(int srcX, int srcY, int x, int y, SDL_Texture* texture, bool flip);
	static std::string getMapPath() { return loaded_mapPath; }
};