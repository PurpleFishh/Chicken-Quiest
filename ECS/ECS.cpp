#include "../ECS/ECS.h"
#include "../Layering/Layering.h"

// Stergem entitatile inactive
void System::inactive_verify()
{
	for (auto& entity : entities)
	{
		if (entity != nullptr)
			if (!entity->isActive())
			{
				Layers::removeEntity(Layers::scenGame, entity.get());
				entities.erase(std::remove_if(std::begin(entities), std::end(entities),
					[](const std::unique_ptr<Entity>& mEntity)
					{
						return !mEntity->isActive();
					}),
					std::end(entities));
			}
	}
}