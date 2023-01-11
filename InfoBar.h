#pragma once
#include "TextComponent.h"
#include <map>

class InfoBar : public TextComponent
{
private:
	std::map<std::string, int> bar_messages;
	SDL_Color color;
public:
	InfoBar(const std::string& text, const SDL_Color& color);

	void init() override;
	
	void display();
	void setLives(int lives);
	void setTimeUntilEgg(int time);
	void playerDeath();
};

