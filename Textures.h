#pragma once

#include "SDL_image.h"
#include "TextureManager.h"
#include "Animation.h"
#include <vector>
#include <map>
#include <string>
#define animations_type std::map<std::string, Animation>

using namespace std;

class Textures {
private:
	static bool loaded_textures, loaded_textures_menu, loaded_animations;
public:
	static vector<SDL_Texture*> textures;
	static vector<SDL_Texture*> textures_menu;
	static vector<animations_type> animations;
	static vector<SDL_Texture*> animations_textures;
	
	static void loadGameTextures();
	static void loadMenuTextures();
	static void loadAnimations();
	static void loadall();
	static void clear();
};
