#include "ECS.h"
#include "Layering.h"

// Stergem entitatile inactive
void System::inactive_verify()
{
	for (auto& entity : entities)
	{
		if (entity != nullptr)
			if (!entity->isActive())
			{
				Layers::removeEntity(entity.get());
				entities.erase(std::remove_if(std::begin(entities), std::end(entities),
					[](const std::unique_ptr<Entity>& mEntity)
					{
						return !mEntity->isActive();
					}),
					std::end(entities));
			}
	}
	//cout << entities.size() << ' ' << Layers::getLayer(Layers::layerPlayer).size() << endl;
}