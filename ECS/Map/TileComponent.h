#pragma once

#include "../ECS.h"
#include "SDL_image.h"

/**
* @brief TileComponent class used for map tiles
*/
class TileComponent : public Component
{
private:
	/// <summary>
	/// scrRect is the source rectangle of the tile, destRect is the destination rectangle of the tile
	/// </summary>
	SDL_Rect scrRect, destRect;
	/// <summary>
	/// texture is the texture of the tile
	/// </summary>
	SDL_Texture* texture;
	/// <summary>
	/// flip is a boolean that determines if the tile is flipped or not
	/// </summary>
	bool flip = false;
public:
	/**
	* @brief TileComponent constructor
	* @param srcX is the x position of the tile in the tileset
	* @param srcY is the y position of the tile in the tileset
	* @param x is the x position of the tile on the map
	* @param y is the y position of the tile on the map
	* @param tilesize is the size of the tile
	* @param tilescale is the scale of the tile
	* @param path is the path to the tileset
	*/
	TileComponent(int srcX, int srcY, int x, int y, int tilesize, int tilescale, const char* path);
	/**
	* @brief TileComponent constructor
	* @param srcX is the x position of the tile in the tileset
	* @param srcY is the y position of the tile in the tileset
	* @param x is the x position of the tile on the map
	* @param y is the y position of the tile on the map
	* @param tilesize is the size of the tile
	* @param tilescale is the scale of the tile
	* @param texture is the texture of the tile
	*/
	TileComponent(int srcX, int srcY, int x, int y, int tilesize, int tilescale, SDL_Texture* texture);
	/**
	* @brief TileComponent constructor
	* @param srcX is the x position of the tile in the tileset
	* @param srcY is the y position of the tile in the tileset
	* @param x is the x position of the tile on the map
	* @param y is the y position of the tile on the map
	* @param tilesize is the size of the tile
	* @param tilescale is the scale of the tile
	* @param texture is the texture of the tile
	* @param flip is a boolean that determines if the tile is flipped or not
	*/
	TileComponent(int srcX, int srcY, int x, int y, int tilesize, int tilescale, SDL_Texture* texture, bool flip);
	
	void init() override;

};