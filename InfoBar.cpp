#include "InfoBar.h"
#include "Layering.h"
#include "EggBoom.h"
#include <string>

InfoBar::InfoBar(const std::string &text, const SDL_Color &color) : TextComponent(text, color)
{
	this->color = color;
}

void InfoBar::display()
{
	std::string text;
	for (auto& message : bar_messages)
	{
		text += message.first;
		if (message.first == "Time until egg: " && message.second == 0)
			text += "Ready";
		else
			text +=  std::to_string(message.second);
		text += "    ";
	}
	setText(text, color);
}

void InfoBar::init()
{
	TextComponent::init();
	bar_messages["Lives: "] = EntityConstructor::PlayerLives;
	bar_messages["Time until egg: "] = 0;
	display();
}
void InfoBar::setLives(int lives)
{
	bar_messages["Lives: "] = lives;
	display();
}
void InfoBar::playerDeath()
{
	bar_messages["Lives: "]--;
	display();
}
void InfoBar::setTimeUntilEgg(int time)
{
	bar_messages["Time until egg: "] = time;
	display();
}