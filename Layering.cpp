#include "Layering.h"

//int Layers::currentSize = 0;
void Layers::add(int scen, Entity* entity, int id)
{
	entity->setLayer_Id(id);
	
	layers[scen].at(id).push_back(entity);
	//if (id > currentSize)
	//	currentSize = id;
}
void Layers::removeEntity(int scen, Entity* entity)
{
	int id = entity->getLayer_Id();
	if(id != -1 && !entity->isActive())
	{
		/*if (id == currentSize)
			while (layers[currentSize].empty())
				currentSize--;*/
		//remove(layers[entity->getLayer_Id()].begin(), layers[entity->getLayer_Id()].end(), entity);
		layers[scen].at(id).erase(std::remove_if(std::begin(layers[scen].at(id)), std::end(layers[scen].at(id)),
			[](Entity* mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(layers[scen].at(id)));
		entity->setLayer_Id(-1);
	}
}
void Layers::clearLayer(int scen, int layer)
{
	for (auto entity : layers[scen].at(layer))
	{
		entity->destroy();
		entity->setLayer_Id(-1);
	}
	layers[scen].at(layer).clear();
}
void Layers::clearLayer(std::vector <Entity *> &layer)
{
	for (auto entity : layer)
	{
		entity->destroy();
		entity->setLayer_Id(-1);
	}
	layer.clear();
}
void Layers::clearScen(int scen)
{
	for (auto& scen_entities : Layers::layers[scen])
		clearLayer(scen_entities);
}
void Layers::renderLayers(int scen)
{
	for (int i = 0; i < LAYERS_NUM; i++)
	{
		for (int j = 0; j < layers[scen].at(i).size(); j++)
		{
			layers[scen].at(i)[j]->draw();
		}
	}
}
void Layers::handlerLayers(int scen)
{
	for (int i = 0; i < LAYERS_NUM; i++)
	{
		for (int j = 0; j < layers[scen].at(i).size(); j++)
		{
			layers[scen].at(i)[j]->handleEvents();
		}
	}
}
void Layers::updateLayers(int scen)
{
	for (int i = 0; i < LAYERS_NUM; i++)
	{
		for (int j = 0; j < layers[scen].at(i).size(); j++)
		{
			layers[scen].at(i)[j]->update();
		}
	}
}

Entity* Layers::getEntityfromLayer(int scen, int layer, int id)
{
	return layers[scen].at(layer)[id];
}
vector<Entity*>& Layers::getLayer(int scen, int layer)
{
	return layers[scen].at(layer);
}
array<vector<Entity*>, LAYERS_NUM>& Layers::getScen(int scen)
{
	return layers[scen];
}