#pragma once
#include "SDL_image.h"
#include <string>

/**
 * @brief Map class that lodes the given map
*/
class Map 
{
private:
	/// <summary>
	/// The path of the loaded map
	/// </summary>
	static std::string loaded_mapPath;
public:
	/// <summary>
	/// The number of rows and columns in the map and the difficulty of the level
	/// </summary>
	static int rows, cols, difficulty;

	/**
	 * @brief Loads the map from the given path
	 * @param mapPath The path of the map
	*/
	static void LoadMap(std::string mapPath);
	/**
	 * @brief Adds a tile to the map
	 * @param srcX The x position of the tile in the tileset
	 * @param srcY The y position of the tile in the tileset
	 * @param x The x position of the tile in the map
	 * @param y The y position of the tile in the map
	 * @param texture The texture of the tileset
	*/
	static void addTile(int srcX, int srcY, int x, int y, SDL_Texture* texture);
	/**
	 * @brief Adds a tile to the map
	 * @param srcX The x position of the tile in the tileset
	 * @param srcY The y position of the tile in the tileset
	 * @param x The x position of the tile in the map
	 * @param y The y position of the tile in the map
	 * @param texture The texture of the tileset
	 * @param flip Whether the tile should be flipped or not
	*/
	static void addTile(int srcX, int srcY, int x, int y, SDL_Texture* texture, bool flip);
	/**
	* @brief Get the map path that is loded
	* @return return the map path that is loded 
	*/
	static std::string getMapPath() { return loaded_mapPath; }
};