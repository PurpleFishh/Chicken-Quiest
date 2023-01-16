#pragma once

class GameInfoStorage
{
private:
	static short Score, Best_Score;
public:
	static short PlayerLives, EnemiesAlive;
	static bool PlayerWon;

	static void ScoreAdd(short score) { Score += score; }
	static void ScoreSub(short score) { Score = Score - score < 0 ? 0 : Score - score; }
	static void ScoreReset() { Score = 0; }
	static short GetScore() { return Score; }
	static short GetBest_Score() { return Best_Score; }

	static void saveInformations();
};