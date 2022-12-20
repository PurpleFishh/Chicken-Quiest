#include "TextureManager.h"
#include "SDL.h"
#include "Game.h"
#include "settings.h"


SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* surface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
	// Desenam doar ce se vede pe ecran
	if (dest.x >= - TILE_SIZE && dest.x <= SCR_W + TILE_SIZE && dest.y >= -TILE_SIZE && dest.y <= SCR_H + TILE_SIZE)
		SDL_RenderCopy(Game::renderer, texture, nullptr, &dest);
}