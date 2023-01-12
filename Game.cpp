#include "Game.h"
#include "Map/Map.h"
#include "ECS/Components.h"
#include "Utils/TexturesTools/Textures.h"
#include "Layering/Layering.h"
#include "Utils/Eggs/ChickenAttack.h"
#include "ElementsConstructors/ScenesManager.h"
#include <iostream>

SDL_Renderer* Game::renderer = nullptr;

System ECS_Manager;
SDL_Event Game::event;
const Uint8* Game::keys_state;
Vector2D Game::mouse_pos;
bool Game::isRunning;
TTF_Font* Game::gameFont;

map<int, array<vector<Entity*>, LAYERS_NUM>> Layers::layers;
stack<int> Layers::ScenesStack;
Entity* ChickenAttack::egg = nullptr;

Game::Game()
{
	isRunning = false;
	window = nullptr;
	renderer = nullptr;
}

Game::~Game()
{
	Textures::clear();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_CloseFont(gameFont);
	TTF_Quit();

	std::cout << "Game closed!";
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{

	int fullscrenncode = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscrenncode);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		Textures::loadall();

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	int imgFlags = IMG_INIT_PNG;
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		stopGame();
	}
	gameFont = TTF_OpenFont("assets/font/minecraft_font.ttf", 28);
	if (gameFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		stopGame();
	}

	keys_state = SDL_GetKeyboardState(0);
	ScenesManager::showMain_Menu();
}


void Game::handleEvents()
{
	while (SDL_PollEvent(&event))
	{
		if (Game::event.type == SDL_MOUSEMOTION || Game::event.type == SDL_MOUSEBUTTONDOWN || Game::event.type == SDL_MOUSEBUTTONUP)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			mouse_pos.x = (x), mouse_pos.y = (y);
		}
		//ECS_Manager.handleEvents();
		Layers::handlerLayers(ScenesManager::getShowingScen());
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (ScenesManager::getShowingScen() == Layers::scenMainMenu)
				stopGame();
			//else if (ScenesManager::getShowingScen() == Layers::scenPauseMenu)
			//	ScenesManager::popScen();
			else if (ScenesManager::getShowingScen() == Layers::scenGame)
				ScenesManager::showPause_Menu();
			break;
		default:
			break;
		}
	}
	ECS_Manager.handleEvents();
}

void Game::update()
{
	if (CameraTarget::hasTarget)
		CameraTarget::cameraOffset = CameraTarget::camera;

	ECS_Manager.inactive_verify();
	Layers::updateLayers(ScenesManager::getShowingScen());
	if (CameraTarget::hasTarget)
		CameraTarget::Cameraupdate();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	Layers::renderLayers(ScenesManager::getShowingScen());

	SDL_RenderPresent(renderer);
}
