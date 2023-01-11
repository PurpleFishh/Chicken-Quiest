#pragma once
#include "SpriteComponent.h"
#include "Game.h"
#include <SDL_ttf.h>
class TextComponent : public SpriteComponent
{
private:
	std::string text;
	SDL_Color color;
public:
    TextComponent(const std::string& text, const SDL_Color& color);

	void init() override;
	
	void setText(const std::string& text, const SDL_Color& color);
};
