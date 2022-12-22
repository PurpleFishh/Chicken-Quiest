#include "Game.h"
#include "Map.h"
#include "Components.h"
#include "Textures.h"
#include "Layering.h"
#include "Collision.h"
#include <iostream>

SDL_Renderer* Game::renderer = nullptr;

System ECS_Manager;
SDL_Event Game::event;
const Uint8* Game::keys_state;

array<vector<Entity*>, LAYERS_NUM> Layers::layers;

auto& player(ECS_Manager.addEntity());

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
	keys_state = SDL_GetKeyboardState(0);

	player.addCompoent<DynamicCollisionComponent>();
	player.addCompoent<PositionComponent>(64, 0, PLAYER_H, PLAYER_W, 1.0f, 1, true);
	//player.addCompoent<PositionComponent>(0, 0, 43, 64, 1, 1, true);
	player.addCompoent<KeyboardControllerComponent>();
	player.addCompoent<SpriteComponent>(Textures::textures.at(2));
	player.addCompoent<CollisionComponent>("player");
	player.addCompoent<CameraTarget>();
	Layers::add(&player, Layers::layerPlayer);

	/*auto& enemy1 = ECS_Manager.addEntity();
	enemy1.addCompoent<PositionComponent>(128, 64, 43, 64, 0.5f, 1, true);
	enemy1.addCompoent<SpriteComponent>(Textures::textures.at(3));
	enemy1.addCompoent<DynamicCollisionComponent>();
	enemy1.addCompoent<AiBehaviour>();
	enemy1.addCompoent<CollisionComponent>("enemy");
	Layers::add(&enemy1, Layers::layerEnemy);*/

	/*auto& enemy2 = ECS_Manager.addEntity();
	enemy2.addCompoent<PositionComponent>(128, 64, 43, 64, 0.3f, 1, true);
	enemy2.addCompoent<DynamicCollisionComponent>();
	enemy2.addCompoent<AiBehaviour>();
	enemy2.addCompoent<SpriteComponent>(Textures::textures.at(3));
	enemy2.addCompoent<CollisionComponent>("enemy");
	Layers::add(&enemy2, Layers::layerEnemy);*/
	
	Map::LoadMap(lvl1Map_path);
}

void Game::handleEvents()
{
	while (SDL_PollEvent(&event))
	{
		ECS_Manager.handleEvents();
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			isRunning = false;
			break;
		default:
			break;
		}
	}
	ECS_Manager.handleEvents();
}

void Game::update()
{
	CameraTarget::cameraOffset = CameraTarget::camera;

	ECS_Manager.inactive_verify();
	ECS_Manager.update();

	CameraTarget::Cameraupdate();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	Layers::renderLayers();
	
	SDL_RenderPresent(renderer);
}