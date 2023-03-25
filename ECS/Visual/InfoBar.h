#pragma once
#include "TextComponent.h"
#include <map>

/**
* @class InfoBar
* @brief Class that will display the information about the game - lives, time, enemies, score, best score
*/
class InfoBar : public TextComponent
{
private:
	/// <summary>
	/// Map of what information to display in the Infobar
	/// </summary>
	std::map<std::string, int> bar_messages;
	/// <summary>
	/// Informations about the game that will be displayed - lives, time, enemies, score, best score
	/// </summary>
	bool lives, time, enemies, score, best_score;
	/// <summary>
	/// The color of the text
	/// </summary>
	SDL_Color color;
public:
	/**
	* @brief Constructor
	* @param text Text to display
	* @param color Color of the text
	* @param facilities Facilities of the InfoBar
	*/
	InfoBar(const std::string& text, const SDL_Color& color, const std::string &facilities);

	void init() override;
	
	/**
	* @brief It will check the needed features in the bar_messages map that the user wants
	* @param facilities Facilities of the InfoBar
	*/
	void decodeFacilities(const std::string& facilities);
	/**
	* @brief Display the InfoBar
	*/
	void display();
	/**
	* @brief Set the lives of the player
	* @param lives Number of lives
	*/
	void setLives(int lives);
	/**
	* @brief Set the number of second until the egg will explode
	* @param time Number of seconds
	*/
	void setTimeUntilEgg(int time);
	/**
	* @brief Called when the player dies to update the number of lives
	*/
	void playerDeath();
	/**
	* @brief Called when the enemy dies to update the number of enemies
	*/
	void enemyDeath();
	/**
	* @brief Called when the score suferes a change to update the score
	*/
	void scoreUpdate();
};

