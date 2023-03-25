#include<iostream>
#include "Game.h"
#include "SDL.h"
#include "settings.h"

using namespace std;

/**
* @brief Main function
* @details It starts the game and execute the game loop, calls the ECS manager functions
*/
int main(int argc, char* args[])
{
	Game* game = new Game();
	game->init("Chicken Quiest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_W, SCR_H, false);
	
	float time1 = 0, time2 = 0, delay;
	
	while (game->getRunning())
	{
		time1 = SDL_GetTicks();
		
		game->handleEvents();
		game->update();
		game->render();

		time2 = SDL_GetTicks();
		delay = (delta_time - time2 + time1);
		if (delay < 0)
			delay = 0;
		SDL_Delay(delay);
	}
	delete game;
	
	return 0;
}