#pragma once

#include "../settings.h"
#include "../ECS/ECS.h"

#include <array>
#include <vector>
#include <map>
#include <stack>

using namespace std;

class Layers
{
private:
	//static int currentSize;

public:
	enum scenes
	{
		scenMainMenu,
		scenLevelsMenu,
		scenPauseMenu,
		scenGame,
		scenGameOver,
		scenGameWin
	};

	// Layers rendering order
	enum class game_layers
	{
		layerCollision,
		layerBackground,
		layerMap,
		layerGoldenEggs,
		layerPlayer,
		layerEnemy,
		layerEggs,
		layerExplosion,
		layerBar
	};
	enum class main_menu_layers
	{
		layerBackground,
		layerButtons,
		layerLogo
	};
	enum class levels_menu_layers
	{
		layerBackground,
		layerButtons
	};
	enum class pause_menu_layers
	{
		layerBackground,
		layerButtons,
		layerBanner
	};
	enum class win_screen_layers
	{
		layerBackground,
		layerButtons,
		layerBanner
	};
	enum class gameover_screen_layers
	{
		layerBackground,
		layerButtons,
		layerBanner
	};
	//static array<vector<Entity*>, LAYERS_NUM> layers;
	static map<int, array<vector<Entity*>, LAYERS_NUM>> layers;
	static stack<int> ScenesStack;

	static void add(int scen, Entity* entity, int id);

	static void removeEntity(int scen, Entity* entity);
	static void clearLayer(int scen, int layer);
	static void clearLayer(std::vector<Entity*>& layer);
	static void clearScen(int scen);

	static void renderLayers(int scen);
	static void handlerLayers(int scen);
	static void updateLayers(int scen);

	static Entity* getEntityfromLayer(int scen, int layer, int id);
	static vector<Entity*>& getLayer(int scen, int layer);
	static array<vector<Entity*>, LAYERS_NUM>& getScen(int scen);
};
