#pragma once

#include "SDL.h"
#include <SDL_ttf.h>
#include "ECS/ECS.h"
#include "Utils/Vector2D.h"

class Game
{
private:
	static bool isRunning;
	SDL_Window* window;
	
public:
	Game();
	~Game();
	
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static const Uint8* keys_state;
	static Vector2D mouse_pos;
	static TTF_Font* gameFont;

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();

	inline bool getRunning() { return isRunning; }
	static void stopGame() { isRunning = false; }
};
