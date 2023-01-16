#include "InfoBar.h"
#include "../../Layering/Layering.h"
#include "../../Utils/Eggs/EggBoom.h"
#include "../../Utils/InfoStorage/GameInfoStorage.h"
#include <string>

InfoBar::InfoBar(const std::string& text, const SDL_Color& color, const std::string& facilities) : TextComponent(text, color)
{
	this->color = color;
	decodeFacilities(facilities);
}

void InfoBar::decodeFacilities(const std::string& facilities)
{
	if (facilities.find("lives") != string::npos)
		lives = true;
	if (facilities.find("time") != string::npos)
		time = true;
	if (facilities.find("enemies") != string::npos)
		enemies = true;
	if (facilities.find("best") != string::npos)
		best_score = true;
	if (facilities.find("score") != string::npos)
		score = true;
	
}

void InfoBar::display()
{
	std::string text;
	for (auto& message : bar_messages)
	{
		text += message.first;
		if (message.first == "Time until egg: " && message.second == 0)
			text += "Ready";
		else if (message.first == "Enemies: " && message.second == 0)
			text += "No enemies";
		else if (message.first == "Best Score: ")
		{
			message.second = GameInfoStorage::GetBest_Score();
			text += std::to_string(message.second);
		}
		else
			text += std::to_string(message.second);
		text += "    ";
	}
	setText(text, color);
}

void InfoBar::init()
{
	TextComponent::init();
	if (lives)
		bar_messages["Lives: "] = GameInfoStorage::PlayerLives;
	if (time)
		bar_messages["Time until egg: "] = 0;
	if (score)
		bar_messages["Score: "] = 0;
	if (enemies)
		bar_messages["Enemies: "] = GameInfoStorage::EnemiesAlive;
	if (best_score)
		bar_messages["Best Score: "] = GameInfoStorage::GetBest_Score();
	display();
}
void InfoBar::setLives(int lives)
{
	if (lives)
		bar_messages["Lives: "] = lives;
	display();
}
void InfoBar::playerDeath()
{
	if (lives)
		bar_messages["Lives: "]--;
	scoreUpdate();
	display();
}
void InfoBar::enemyDeath()
{
	if (enemies)
		bar_messages["Enemies: "]--;
	scoreUpdate();
	display();
}
void InfoBar::scoreUpdate()
{
	if (score)
		bar_messages["Score: "] = GameInfoStorage::GetScore();
	display();
}
void InfoBar::setTimeUntilEgg(int time)
{
	if (this->time)
		bar_messages["Time until egg: "] = time;
	scoreUpdate();
	display();
}