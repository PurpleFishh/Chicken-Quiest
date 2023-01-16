#pragma once
#include "TextComponent.h"
#include <map>

class InfoBar : public TextComponent
{
private:
	std::map<std::string, int> bar_messages;
	bool lives, time, enemies, score, best_score;
	SDL_Color color;
public:
	InfoBar(const std::string& text, const SDL_Color& color, const std::string &facilities);

	void init() override;
	
	void decodeFacilities(const std::string& facilities);
	void display();
	void setLives(int lives);
	void setTimeUntilEgg(int time);
	void playerDeath();
	void enemyDeath();
	void scoreUpdate();
};

