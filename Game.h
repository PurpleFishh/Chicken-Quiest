#pragma once

#include "SDL.h"

class Game
{
private:
	bool isRunning;
	SDL_Window* window;
public:
	Game();
	~Game();
	
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static const Uint8* keys_state;
	
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();

	inline bool getRunning() { return isRunning; }
};
