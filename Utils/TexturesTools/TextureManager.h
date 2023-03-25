#pragma once
#include "SDL_image.h"

/**
* @brief This class is used to render the needed textures.
*/
class TextureManager
{
private:

public:
	/**
	* @brief Render a texture from a file.
	* @param fileName The file name of the texture.
	*/
	static SDL_Texture* LoadTexture(const char* fileName);
	/**
	* @brief Render a texture from a SDL_Texture.
	* @param texture The SDL_Texture to render.
	* @param src The source rectangle.
	* @param dest The destination rectangle.
	* @param flip The flip type, if the texture is fliped or not.
	* @param renderOnlyWhatsOnScreen If true, the texture will be rendered only if it visible on the screen.
	*/
	static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip, bool renderOnlyWhatsOnScreen);
};