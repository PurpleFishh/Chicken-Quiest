#include "Textures.h"


vector<SDL_Texture*> Textures::textures;
void Textures::loadall()
{
	textures.push_back(TextureManager::LoadTexture("assets/grass.png"));
	textures.push_back(TextureManager::LoadTexture("assets/dirt.png"));;
	textures.push_back(TextureManager::LoadTexture("assets/chicken_cut.png"));
	textures.push_back(TextureManager::LoadTexture("assets/pig1.png"));
}

void Textures::clear()
{
	for (auto& texture : textures)
	{
		SDL_DestroyTexture(texture);
	}
}