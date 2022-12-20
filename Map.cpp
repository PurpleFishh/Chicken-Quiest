#include "Map.h"
#include "Textures.h"
#include "Game.h"
#include "TileComponent.h"
#include "Layering.h"
#include "CollisionComponent.h"
#include <fstream>

using namespace std;

extern System ECS_Manager;
int Map::rows = 0, Map::cols = 0;

void Map::LoadMap(const char* mapPath)
{
	ifstream mapfile(mapPath);
	int tileType = 0;
	char chr;
	mapfile >> rows >> cols;
	mapfile.get();
	
	mapfile.get(chr);
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			tileType = 0;
			while (chr != ',' && chr != '\n')
			{
				tileType = tileType * 10 + atoi(&chr);
				mapfile.get(chr);
			}
			addTile(0, 0, col * 64, row * 64, Textures::textures.at(tileType));
			mapfile.get(chr);
		}
	}
	//mapfile.get();
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			mapfile.get(chr);
			tileType = atoi(&chr);
			if (tileType == 1)
			{
				auto* tile = Layers::getEntityfromLayer(Layers::layerMap, row * (cols)+col);
				//auto* tile = Game::ECS_Manager.getEntityfromLayer(layerMap, row * (cols) + col);
				Layers::add(tile, Layers::layerCollision);
				//Game::ECS_Manager.addToLayer(tile, layerCollision);
				tile->addCompoent<CollisionComponent>("ground");
			}
			mapfile.get();
		}
	}
	mapfile.close();
}

void Map::addTile(int srcX, int srcY, int x, int y, SDL_Texture* texture)
{
	auto& tile = ECS_Manager.addEntity();
	tile.addCompoent<TileComponent>(srcX, srcY, x, y, 64, 1, texture);

	Layers::add(&tile, Layers::layerMap);
}