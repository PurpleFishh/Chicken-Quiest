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

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip, bool renderOnlyWhatsOnScreen)
{
	// Desenam doar ce se vede pe ecran
	if (!renderOnlyWhatsOnScreen || dest.x >= - TILE_SIZE * 2 && dest.x <= SCR_W + TILE_SIZE * 2 && dest.y >= -TILE_SIZE * 2 && dest.y <= SCR_H + TILE_SIZE * 2)
		SDL_RenderCopyEx(Game::renderer, texture, &src, &dest, NULL, NULL, flip);
}