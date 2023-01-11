#pragma once
#include <array>
#include "settings.h"
#include <string>

class ScenesManager
{
private:
	static std::array<bool, SCENES_NUM> scene_loaded;
public:
	static void popScen();
	static int getShowingScen();
	static void destroyShowingScen();

	static void startLevel(std::string mapPath);
	static void showMain_Menu();
	static void showLevels_Menu();
	static void showPause_Menu();
	static void showWin_Screen();
	static void showGameOver_Screen();
};

