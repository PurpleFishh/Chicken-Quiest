#pragma once
#include "ECS.h"
#include "Vector2D.h"
#include "SDL_ttf.h"

/**
* @class EntityConstructor
* @brief Class that contains all the methods for creating the game elements
*/
class EntityConstructor
{
private:
public:
	/// <summary>
	/// Player spawn position
	/// Winning egg spawn position
	/// </summary>
	static Vector2D player_spawn_position, golden_egg_spawn_position;
	static bool PlayerWon;
	static short PlayerLives;
	
	/// <summary>
	/// Empty tile for the map
	/// </summary>
	static Entity& emptyTile;
	/**
	* @brief Method that creates and spawn the playe
	* @param spawn_position - position where the player will be created
	* @return return reference to the player
	*/
	static Entity& spawnPlayer(const Vector2D& spawn_position);
	/**
	* @brief Method that creates and spawn the enemy
	* @param spawn_position - position where the enemy will be created
	* @return return reference to the enemy
	*/
	static Entity& spawnEnemy(const Vector2D& spawn_position);
	/**
	* @brief Method that creates and spawn the egg
	* @param spawn_position - position where the egg will be created
	* @return return reference to the egg
	*/
	static Entity& spawnEgg(const Vector2D& spawn_position);
	/**
	* @brief Method that creates and spawn the golden egg
	* @param spawn_position - position where the golden egg will be created
	* @return return reference to the golden egg
	*/
	static Entity& spawnGoldenEgg(const Vector2D& spawn_position);
	/**
	* @brief Method that creates and spawn an explosion
	* @param spawn_position - position where the explosion will be created
	*/
	static Entity& spawnExplosion(const Vector2D& spawn_position);
	/**
	* @brief Method that creates and spawn the background
	* @param scen - scene where the background will be created
	* @param layer - layer where the background will be created
	* @param spawn_position - position where the background will be created
	* @param texture - texture that will be used for the background
	* @param w - width of the background
	* @param h - height of the background
	* @param scrw - width of source image
	* @param scrh - height of source image
	* @return return reference to the background
	*/
	static Entity& spawnBackground(int scen, int layer, const Vector2D& spawn_position, SDL_Texture* texture, int w, int h, int scrw, int scrh);
	/**
	* @brief Method that creates and spawn the text
	* @param spawn_position - position where the text will be created
	* @param text - text that will be displayed
	* @return return reference to the text
	*/
	static Entity& spawnText(const Vector2D& spawn_position, std::string text);
<<<<<<< Updated upstream:EntityConstructor.h
	static Entity& spawnInfoBar(const Vector2D& spawn_position, SDL_Color color);
=======
	/**
	* @brief Method that creates and spawn the info bar
	* @param scen - scene where the info bar will be created
	* @param layer - layer where the info bar will be created
	* @param spawn_position - position where the info bar will be created
	* @param color - color of the info bar
	* @param facilities - facilities that will be displayed
	* @return return reference to the info bar
	*/
	static Entity& spawnInfoBar(int scen, int layer, const Vector2D& spawn_position, SDL_Color color, const std::string& facilities);
>>>>>>> Stashed changes:ElementsConstructors/EntityConstructor.h

	/**
	* @brief Method that called after the animation play once
	* @details This function will destory the entity after the animation plays
	* @param entity - entity that called the method
	*/
	static void AnimationAfter_destroyEntity(Entity* entity);
	/**
	* @brief Method that called after the animation play once
	* @details This function will spawn the win screen after the animation player wins animation plays, updates the stats and destroy the level
	* @param entity - entity that called the method
	*/
	static void AnimationAfter_playerWin(Entity* entity);
};

