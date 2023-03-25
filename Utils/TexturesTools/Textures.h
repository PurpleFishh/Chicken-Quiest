#pragma once

#include "SDL_image.h"
#include "TextureManager.h"
#include "Animation.h"
#include <vector>
#include <map>
#include <string>
#define animations_type std::map<std::string, Animation>

using namespace std;

/**
 * @brief Class that loads all textures and animations
*/
class Textures {
private:
	/// <summary>
	/// Flag that indicates if textures are loaded
	/// </summary>
	static bool loaded_textures, loaded_textures_menu, loaded_animations;
public:
	/// Vector that contains all textures for the gameplay
	static vector<SDL_Texture*> textures;
	/// Vector that contains all textures of the menu
	static vector<SDL_Texture*> textures_menu;
	/// Vector that stores all animations
	static vector<animations_type> animations;
	/// Vector that stores all textures of the animations
	static vector<SDL_Texture*> animations_textures;
	
	/**
	* @brief Loads all the game textures
	*/
	static void loadGameTextures();
	/**
	* @brief Loads all the menu textures
	*/
	static void loadMenuTextures();
	/**
	* @brief Loads all the animations
	*/
	static void loadAnimations();
	/**
	* @brief Loads all the textures used by the game
	*/
	static void loadall();
	/**
	* @brief Clears all the textures
	*/
	static void clear();
};
