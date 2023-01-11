#include "TextComponent.h"

TextComponent::TextComponent(const std::string &text, const SDL_Color& color)
{
	this->text = text;
	this->color = color;
}

void TextComponent::init()
{
	SpriteComponent::init();
	setText(text, color);
}

void TextComponent::setText(const std::string& text, const SDL_Color& color)
{
	if (texture)
		SDL_DestroyTexture(texture);

	SDL_Surface* textSurface = TTF_RenderText_Solid(Game::gameFont, text.c_str(), color);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
		if (texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			posdetails->width = srcRect.w = textSurface->w;
			posdetails->height = srcRect.h = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
}