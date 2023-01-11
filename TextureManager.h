#pragma once
#include "SDL_image.h"

class TextureManager
{
private:

public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip, bool renderOnlyWhatsOnScreen);
};