#pragma once

#include "settings.h"
#include "ECS.h"

#include <array>
#include <vector>

using namespace std;

class Layers
{
private:
	static int currentSize;
	
public:
	// Layers rendering order
	enum layers
	{
		layerCollision,
		layerMap,
		layerPlayer,
		layerEnemy
	};
	static array<vector<Entity*>, LAYERS_NUM> layers;

	static void add(Entity* entity, int id);
	static void removeEntity(Entity* entity);
	static void renderLayers();
	static Entity* getEntityfromLayer(int layer, int id);
	static vector<Entity*>& getLayer(int layer);
};
