#include "GameInfoStorage.h"
#include "../../settings.h"
#include <fstream>

bool GameInfoStorage::PlayerWon = false;
short GameInfoStorage::PlayerLives = 0;
short GameInfoStorage::EnemiesAlive = 0;
short GameInfoStorage::Score = 0;
short GameInfoStorage::Best_Score = 0;

void GameInfoStorage::saveInformations()
{
	std::ifstream readfile;
	readfile.open(saveGameInfoFile);
	if (readfile)
		readfile >> Best_Score;
	else
		Best_Score = 0;
	readfile.close();
	
	std::ofstream file;
	file.open(saveGameInfoFile);
	//file >> score_old;
	if (Best_Score < Score)
	{
		file.clear();
		Best_Score = Score;
		file << Score;
	}
	file.close();
}