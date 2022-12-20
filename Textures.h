#pragma once

#include "SDL_image.h"
#include "TextureManager.h"
#include <vector>

using namespace std;

class Textures {
public:
	static vector<SDL_Texture*> textures;
	
	static void loadall();
	static void clear();
};
