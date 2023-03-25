#pragma once
#include <array>
#include "../settings.h"
#include <string>

/**
* @brief This class(abstract class) is responsible for managing the scenes.
*/
class ScenesManager
{
private:
	/// <summary>
	/// Stores what scens are loded
	/// </summary>
	static std::array<bool, SCENES_NUM> scene_loaded;
public:
	/**
	* @brief Pops the top of the scen stack.
	*/
	static void popScen();
	/**
	* @brief Gets the top of the scen stack.
	* @return The top of the scen stack.
	*/
	static int getShowingScen();
	/**
	* @brief Pops and destroys the top of the scen stack.
	*/
	static void destroyShowingScen();

	/**
	* @brief Pushes, lodes and initialize the level scene.
	*/
	static void startLevel(std::string mapPath);
	/**
	* @brief Pushes, lodes and initialize the main menu of the game.
	*/
	static void showMain_Menu();
	/**
	* @brief Pushes, lodes and initialize the levels selection menu of the game.
	*/
	static void showLevels_Menu();
	/**
	* @brief Pushes, lodes and initialize the pause menu of the game.
	*/
	static void showPause_Menu();
	/**
	* @brief Pushes, lodes and initialize the win screen of the game.
	*/
	static void showWin_Screen();
	/**
	* @brief Pushes, lodes and initialize the game over screen of the game.
	*/
	static void showGameOver_Screen();
};

