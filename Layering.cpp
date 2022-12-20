#include "Layering.h"

int Layers::currentSize = 0;
void Layers::add(Entity* entity, int id)
{
	entity->setLayer_Id(id);
	
	layers[id].push_back(entity);
	if (id > currentSize)
		currentSize = id;
}
void Layers::removeEntity(Entity* entity)
{
	int id = entity->getLayer_Id();
	if(id != -1 && !entity->isActive())
	{
		if (id == currentSize)
			while (layers[currentSize].empty())
				currentSize--;
		//remove(layers[entity->getLayer_Id()].begin(), layers[entity->getLayer_Id()].end(), entity);
		layers[id].erase(std::remove_if(std::begin(layers[id]), std::end(layers[id]),
			[](Entity* mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(layers[id]));
		entity->setLayer_Id(-1);
	}
}
void Layers::renderLayers()
{
	for (int i = 0; i <= currentSize; i++)
	{
		for (int j = 0; j < layers[i].size(); j++)
		{
			layers[i][j]->draw();
		}
	}
}

Entity* Layers::getEntityfromLayer(int layer, int id)
{
	return layers[layer][id];
}
vector<Entity*>& Layers::getLayer(int layer)
{
	return layers[layer];
}