#include "Map.h"
#include "../Utils/TexturesTools/Textures.h"
#include "../Game.h"
#include "../ElementsConstructors/EntityConstructor.h"
#include "../ECS/Map/TileComponent.h"
#include "../Layering/Layering.h"
#include "../ECS/Collision/CollisionComponent.h"
#include "../Utils/InfoStorage/GameInfoStorage.h"
#include <fstream>

using namespace std;

extern System ECS_Manager;
int Map::rows = 0, Map::cols = 0, Map::difficulty = 0;
std::string Map::loaded_mapPath;

void Map::LoadMap(std::string mapPath)
{
	loaded_mapPath = mapPath;
	ifstream mapfile(mapPath);

	GameInfoStorage::ScoreReset();
	GameInfoStorage::EnemiesAlive = 0;
	
	mapfile >> difficulty;
	// Setam viteza animatiei dupa noua viteza de mers in functie de dificultate
	int newSpeed = (300 - 45 * (difficulty - 1)) < 80 ? 80 : 300 - 45 * (difficulty - 1);
	Textures::animations.at(1).at("Walk").setSpeed(newSpeed);

	int tileType = 0;
	char chr;
	mapfile >> rows >> cols;
	mapfile.get();

	// Reading the map
	mapfile.get(chr);
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			tileType = 0;
			while (chr != ',' && chr != '\n' && chr != 'f')
			{
				tileType = tileType * 10 + atoi(&chr);
				mapfile.get(chr);
			}

			if(tileType == 0)
				Layers::add(Layers::scenGame, &EntityConstructor::emptyTile, (int)Layers::game_layers::layerMap);
			else
			{
				bool flip = (chr == 'f');
				addTile(0, 0, col * 64, row * 64, Textures::textures.at(tileType - 1), flip);
				if (flip)
					mapfile.get();
			}
			mapfile.get(chr);
		}
	}
	//mapfile.get();
	// Reading the colliders
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			mapfile.get(chr);
			tileType = atoi(&chr);
			if (tileType == 1)
			{
				auto* tile = Layers::getEntityfromLayer(Layers::scenGame, (int)Layers::game_layers::layerMap, row * (cols)+col);
				Layers::add(Layers::scenGame, tile, (int)Layers::game_layers::layerCollision);

				tile->addCompoent<CollisionComponent>("ground");
			}
			mapfile.get();
		}
	}
	mapfile.get();
	// Reading the entities position
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			mapfile.get(chr);
			tileType = atoi(&chr);
			if (chr == 'p')
				EntityConstructor::player_spawn_position = Vector2D(float(col * TILE_SIZE), float(row * TILE_SIZE));
			if (chr == 'e')
			{
				EntityConstructor::spawnEnemy(Vector2D(float(col * TILE_SIZE), float(row * TILE_SIZE)));
				GameInfoStorage::EnemiesAlive++;
			}
			if (chr == 'g')
				EntityConstructor::golden_egg_spawn_position = Vector2D(float(col * TILE_SIZE), float(row * TILE_SIZE));
			mapfile.get();
		}
	}
	mapfile.close();
}

void Map::addTile(int srcX, int srcY, int x, int y, SDL_Texture* texture)
{
	auto& tile = ECS_Manager.addEntity();
	tile.addCompoent<TileComponent>(srcX, srcY, x, y, TILE_SIZE, 1, texture);

	Layers::add(Layers::scenGame, &tile, (int)Layers::game_layers::layerMap);
}
void Map::addTile(int srcX, int srcY, int x, int y, SDL_Texture* texture, bool flip)
{
	auto& tile = ECS_Manager.addEntity();
	tile.addCompoent<TileComponent>(srcX, srcY, x, y, TILE_SIZE, 1, texture, flip);

	Layers::add(Layers::scenGame, &tile, (int)Layers::game_layers::layerMap);
}