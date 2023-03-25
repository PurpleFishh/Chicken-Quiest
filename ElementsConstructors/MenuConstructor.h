#pragma once
#include "../ECS/ECS.h"
#include "../Utils/Vector2D.h"
#include <map>
#include <string>

/**
* @class MenuConstructor
* @brief Class that contains all the methods for creating the menu elements
*/
class MenuConstructor
{
public:
	/// <summary>
	/// Map of the entities(buttons) form the menu and their specialization(what they will do when you interact with them)
	/// </summary>
	static std::map<Entity* ,std::string> menu_entities_specialization;

	/**
	* @brief Method that creates the background of the menu
	* @param spawn_position - position where the background will be created
	* @return return reference to the background
	*/
	static Entity& spawnBackground(const Vector2D& spawn_position);
	/**
	* @brief Method that creates the logo of the menu
	* @param spawn_position - position where the logo will be created
	* @return return reference to the logo
	*/
	static Entity& spawnLogo(const Vector2D& spawn_position);
	/**
	* @brief Method that creates the button of the menu
	* @param scen - scene where the button will be created
	* @param layer - layer where the button will be created
	* @param spawn_position - position where the button will be created
	* @param specialization - specialization of the button(what it will do when you interact with it)
	* @param texture_id - id of the texture that will be used for the button
	* @param w - width of the button
	* @param h - height of the button
	* @param scrw - width of source image
	* @param scrh - height of source image
	* @return return reference to the button
	*/
	static Entity& spawnButton(int scen, int layer, const Vector2D& spawn_position, std::string specialization, int texture_id, int w, int h, int scrw, int scrh);
};

