#pragma once

/**
* @brief Class that stores all the game information that will be saved at the end of the game
*/
class GameInfoStorage
{
private:
	/// <summary>
	/// Score of the current game and the alltime best score
	/// </summary>
	static short Score, Best_Score;
public:
	/// <summary>
	/// Number of lives of the player and the number of enemies alive
	/// </summary>
	static short PlayerLives, EnemiesAlive;
	/// <summary>
	/// If the player won the game
	/// </summary>
	static bool PlayerWon;

	/**
	 * @brief Add or substract score to the current score
	  * @param score Score to add
	*/
	static void ScoreAdd(short score) { Score += score; }
	/**
	* @brief Add or substract score to the current score
	  * @param score Score to substract
	*/
	static void ScoreSub(short score) { Score = Score - score < 0 ? 0 : Score - score; }
	/**
	* @brief Reset the score to 0
	*/
	static void ScoreReset() { Score = 0; }
	/**
	* @brief Get the current score
	*/
	static short GetScore() { return Score; }
	/**
	* @brief Get the best score
	*/
	static short GetBest_Score() { return Best_Score; }

	/**
	 * @brief Save the game information in the file form settings.h
	*/
	static void saveInformations();
};