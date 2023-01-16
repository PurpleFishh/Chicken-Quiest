#include "ScenesManager.h"
#include "../Map/Map.h"
#include "../ElementsConstructors/EntityConstructor.h"
#include "../Utils/Vector2D.h"
#include "../Layering/Layering.h"
#include "../ElementsConstructors/MenuConstructor.h"
#include "../Utils/TexturesTools/Textures.h"

std::array<bool, SCENES_NUM> ScenesManager::scene_loaded;

void ScenesManager::popScen()
{
	Layers::ScenesStack.pop();
}
int ScenesManager::getShowingScen()
{
	return Layers::ScenesStack.top();
}
void ScenesManager::destroyShowingScen()
{
	int scen = getShowingScen();
	popScen();
	Layers::clearScen(scen);
	scene_loaded[scen] = false;	
}

void ScenesManager::startLevel(std::string mapPath)
{
	while (!Layers::ScenesStack.empty())
		destroyShowingScen();
	Layers::ScenesStack.push(Layers::scenGame);
	if (!scene_loaded[Layers::scenGame])
	{
		Map::LoadMap(mapPath);
		EntityConstructor::spawnBackground(Layers::scenGame, (int)Layers::game_layers::layerBackground, Vector2D(0, 0), Textures::textures.at(12),
			(Map::cols * TILE_SIZE), (Map::rows * TILE_SIZE), 1280, 768);
		EntityConstructor::spawnPlayer(EntityConstructor::player_spawn_position);
		EntityConstructor::spawnInfoBar(Layers::scenGame, (int)Layers::game_layers::layerBar, Vector2D(10, 10), SDL_Color{ 255, 255, 255 }, "lives time");
		EntityConstructor::spawnInfoBar(Layers::scenGame, (int)Layers::game_layers::layerBar, Vector2D(10, 50), SDL_Color{ 255, 255, 255 }, "enemies score");

		scene_loaded[Layers::scenGame] = true;
	}
}
void ScenesManager::showMain_Menu()
{
	Layers::ScenesStack.push(Layers::scenMainMenu);
	if (!scene_loaded[Layers::scenMainMenu])
	{
		EntityConstructor::spawnBackground(Layers::scenMainMenu, (int)Layers::main_menu_layers::layerLogo, Vector2D(LOGO_W, SCR_W, 150.f), Textures::textures_menu.at(21),
			LOGO_W, LOGO_H, LOGO_SCR_W, LOGO_SCR_H);
		MenuConstructor::spawnButton(Layers::scenMainMenu, (int)Layers::main_menu_layers::layerButtons, Vector2D(BUTTON_W, SCR_W / 2, (float)(3 * SCR_H / 4)),
			"start level", 0, BUTTON_W, BUTTON_H, BUTTON_SCR_W, BUTTON_SCR_H);
		MenuConstructor::spawnButton(Layers::scenMainMenu, (int)Layers::main_menu_layers::layerButtons, Vector2D(BUTTON_W, 3 * SCR_W / 2, (float)(3 * SCR_H / 4)),
			"exit", 2, BUTTON_W, BUTTON_H, BUTTON_SCR_W, BUTTON_SCR_H);
		EntityConstructor::spawnBackground(Layers::scenMainMenu, (int)Layers::main_menu_layers::layerBackground, Vector2D(0, 0), Textures::textures_menu.at(20),
			SCR_W, SCR_H, 1280, 768);

		scene_loaded[Layers::scenMainMenu] = true;
	}
}
void ScenesManager::showLevels_Menu()
{
	Layers::ScenesStack.push(Layers::scenLevelsMenu);
	if (!scene_loaded[Layers::scenLevelsMenu])
	{
		for (int i = 1; i <= 5; ++i)
			MenuConstructor::spawnButton(Layers::scenLevelsMenu, (int)Layers::levels_menu_layers::layerButtons, Vector2D(400.f + (i - 1) * 200, 200.f),
				std::string("level " + std::to_string(i)), 4 + (i - 1) * 2, BUTTON_W, BUTTON_H, BUTTON_SCR_W, BUTTON_SCR_H);
		MenuConstructor::spawnButton(Layers::scenLevelsMenu, (int)Layers::levels_menu_layers::layerButtons, Vector2D(BUTTON_W, 600, 200.f),
			"back", 14, BUTTON_BACK_W, BUTTON_BACK_H, BUTTON_BACK_SCR_W, BUTTON_BACK_SCR_H);
		EntityConstructor::spawnBackground(Layers::scenLevelsMenu, (int)Layers::levels_menu_layers::layerBackground, Vector2D(0, 0), Textures::textures_menu.at(20),
			SCR_W, SCR_H, 1280, 768);
		EntityConstructor::spawnInfoBar(Layers::scenLevelsMenu, (int)Layers::levels_menu_layers::layerBar, Vector2D(100, SCR_W, 100.f), SDL_Color{ 255, 255, 255 }, "best");
		scene_loaded[Layers::scenLevelsMenu] = true;
	}
}

void ScenesManager::showPause_Menu()
{
	Layers::ScenesStack.push(Layers::scenPauseMenu);
	if (!scene_loaded[Layers::scenPauseMenu])
	{
		MenuConstructor::spawnButton(Layers::scenPauseMenu, (int)Layers::pause_menu_layers::layerButtons, Vector2D(BUTTON_W, SCR_W / 2, (float)(3 * SCR_H / 4)),
			"back", 16, BUTTON_W, BUTTON_H, BUTTON_SCR_W, BUTTON_SCR_H);
		MenuConstructor::spawnButton(Layers::scenPauseMenu, (int)Layers::pause_menu_layers::layerButtons, Vector2D(BUTTON_W, 3 * SCR_W / 2, (float)(3 * SCR_H / 4)),
			"exit level", 2, BUTTON_W, BUTTON_H, BUTTON_SCR_W, BUTTON_SCR_H);
		EntityConstructor::spawnBackground(Layers::scenPauseMenu, (int)Layers::pause_menu_layers::layerBanner, Vector2D(BANNER_W, SCR_W, 200.f), Textures::textures_menu.at(22),
			BANNER_W, BANNER_H, BANNER_SCR_W, BANNER_SCR_H);
		EntityConstructor::spawnBackground(Layers::scenPauseMenu, (int)Layers::pause_menu_layers::layerBackground, Vector2D(0, 0), Textures::textures_menu.at(20),
			SCR_W, SCR_H, 1280, 768);
		scene_loaded[Layers::scenPauseMenu] = true;
	}
}
void ScenesManager::showWin_Screen()
{
	Layers::ScenesStack.push(Layers::scenGameWin);
	if (!scene_loaded[Layers::scenGameWin])
	{
		MenuConstructor::spawnButton(Layers::scenGameWin, (int)Layers::win_screen_layers::layerButtons, Vector2D(BUTTON_W, SCR_W, (float)(3 * SCR_H / 4)),
			"exit level", 2, BUTTON_W, BUTTON_H, BUTTON_SCR_W, BUTTON_SCR_H);
		EntityConstructor::spawnBackground(Layers::scenGameWin, (int)Layers::win_screen_layers::layerBanner, Vector2D(BANNER_W, SCR_W, 200.f), Textures::textures_menu.at(23),
			BANNER_W, BANNER_H, BANNER_SCR_W, BANNER_SCR_H);
		EntityConstructor::spawnBackground(Layers::scenGameWin, (int)Layers::win_screen_layers::layerBackground, Vector2D(0, 0), Textures::textures_menu.at(20),
			SCR_W, SCR_H, 1280, 768);
		scene_loaded[Layers::scenGameWin] = true;
	}
}
void ScenesManager::showGameOver_Screen()
{
	Layers::ScenesStack.push(Layers::scenGameOver);
	if (!scene_loaded[Layers::scenGameOver])
	{
		MenuConstructor::spawnButton(Layers::scenGameOver, (int)Layers::gameover_screen_layers::layerButtons, Vector2D(BUTTON_W, SCR_W / 2, (float)(3 * SCR_H / 4)),
			"retry", 18, BUTTON_W, BUTTON_H, BUTTON_SCR_W, BUTTON_SCR_H);
		MenuConstructor::spawnButton(Layers::scenGameOver, (int)Layers::gameover_screen_layers::layerButtons, Vector2D(BUTTON_W, 3 * SCR_W / 2, (float)(3 * SCR_H / 4)),
			"exit level", 2, BUTTON_W, BUTTON_H, BUTTON_SCR_W, BUTTON_SCR_H);
		EntityConstructor::spawnBackground(Layers::scenGameOver, (int)Layers::gameover_screen_layers::layerBanner, Vector2D(BANNER_W, SCR_W, 200.f), Textures::textures_menu.at(24),
			BANNER_W, BANNER_H, BANNER_SCR_W, BANNER_SCR_H);
		EntityConstructor::spawnBackground(Layers::scenGameOver, (int)Layers::gameover_screen_layers::layerBackground, Vector2D(0, 0), Textures::textures_menu.at(20),
			SCR_W, SCR_H, 1280, 768);
		scene_loaded[Layers::scenGameOver] = true;
	}
}
