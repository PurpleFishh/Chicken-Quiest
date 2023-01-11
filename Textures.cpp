#include "Textures.h"

bool Textures::loaded_textures = false, Textures::loaded_textures_menu = false, Textures::loaded_animations = false;
vector<SDL_Texture*> Textures::textures;
vector<SDL_Texture*> Textures::textures_menu;
vector<animations_type> Textures::animations;
vector<SDL_Texture*> Textures::animations_textures;
void Textures::loadGameTextures()
{
	if (loaded_textures)
		return;
	textures.push_back(TextureManager::LoadTexture("assets/grass_1.png"));
	textures.push_back(TextureManager::LoadTexture("assets/grass_2.png"));
	textures.push_back(TextureManager::LoadTexture("assets/grass_3.png"));
	textures.push_back(TextureManager::LoadTexture("assets/grass_4.png"));
	textures.push_back(TextureManager::LoadTexture("assets/grass_5.png"));
	textures.push_back(TextureManager::LoadTexture("assets/grass_6.png"));
	textures.push_back(TextureManager::LoadTexture("assets/grass_7.png"));
	textures.push_back(TextureManager::LoadTexture("assets/grass_8.png"));
	textures.push_back(TextureManager::LoadTexture("assets/grass_9.png"));
	textures.push_back(TextureManager::LoadTexture("assets/grass_10.png"));
	textures.push_back(TextureManager::LoadTexture("assets/egg.png"));
	textures.push_back(TextureManager::LoadTexture("assets/golden_egg.png"));
	textures.push_back(TextureManager::LoadTexture("assets/sky.png"));
	loaded_textures = true;
}
void Textures::loadMenuTextures()
{
	if (loaded_textures_menu)
		return;
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/play_1.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/play_2.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/exit_1.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/exit_2.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/level1_1.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/level1_2.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/level2_1.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/level2_2.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/level3_1.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/level3_2.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/level4_1.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/level4_2.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/level5_1.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/level5_2.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/back_1.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/back_2.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/resume_1.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/resume_2.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/retry_1.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/buttons/retry_2.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/menu_background.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/logo.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/pause_banner.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/win_banner.png"));
	textures_menu.push_back(TextureManager::LoadTexture("assets/gameover_banner.png"));
	
	loaded_textures_menu = true;
}
void Textures::loadAnimations()
{
	if (loaded_animations)
		return;
	animations_textures.push_back(TextureManager::LoadTexture("assets/chicken_animation.png"));
	animations_type animation;
	Animation idle = Animation(0, 1, 100);
	Animation walk = Animation(1, 8, 210);
	Animation fly = Animation(2, 7, 300);
	Animation eat = Animation(3, 4, 100);
	animation.emplace("Idle", idle);
	animation.emplace("Walk", walk);
	animation.emplace("Fly", fly);
	animation.emplace("Eat", eat);
	animations.push_back(animation);

	//enemy
	animations_textures.push_back(TextureManager::LoadTexture("assets/dog_animation.png"));
	animation.clear();
	walk = Animation(0, 11, 300);
	animation.emplace("Walk", walk);
	//animation.emplace("Walk", walk);
	animations.push_back(animation);

	//explosion
	animations_textures.push_back(TextureManager::LoadTexture("assets/explosion_aniamtion.png"));
	animation.clear();
	idle = Animation(0, 4, 100);
	animation.emplace("Explosion", idle);
	animations.push_back(animation);

	loaded_animations = true;
}

void Textures::loadall()
{
	loadGameTextures();
	loadMenuTextures();
	loadAnimations();
}

void Textures::clear()
{
	for (auto& texture : textures)
	{
		SDL_DestroyTexture(texture);
	}
	for (auto& texture : textures_menu)
	{
		SDL_DestroyTexture(texture);
	}
	for (auto& texture : animations_textures)
	{
		SDL_DestroyTexture(texture);
	}
}