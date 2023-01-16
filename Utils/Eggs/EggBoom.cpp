#include "EggBoom.h"
#include "../../settings.h"
#include "ChickenAttack.h"
#include "../../ECS/Visual/SpriteComponent.h"
#include "../../Game.h"
#include "../../ElementsConstructors/EntityConstructor.h"
#include "../../Layering/Layering.h"
#include "../../ECS/Visual/InfoBar.h"
#include "../../Managers/ErrorHandler/ErrorHandler.h"
#include "../../Map/Map.h"
#include "../../Utils/InfoStorage/GameInfoStorage.h"


EggBoom::EggBoom(int wait_time)
{
	this->wait_time = wait_time;
}

void EggBoom::init()
{
	try {
		dynamic_col = entity->getComponent<DynamicCollisionComponent>();
		if (!entity->hasComponent<DynamicCollisionComponent>())		throw ErrorHandler(typeid(EggBoom).name(), typeid(DynamicCollisionComponent).name());
	}
	catch (ErrorHandler e) { dynamic_col = &entity->addCompoent<DynamicCollisionComponent>(); }
	catch (std::exception& ex) { cout << ex.what() << endl; }
	
	wait_time = wait_time + Map::difficulty;
	for (auto& bars : Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerBar))
		bars->getComponent<InfoBar>()->setTimeUntilEgg(wait_time);
}

void EggBoom::update()
{
	fps_until_sec++;
	if (fps_until_sec >= fps)
	{
		wait_time--;
		fps_until_sec = 0;

		for (auto& bars : Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerBar))
			bars->getComponent<InfoBar>()->setTimeUntilEgg(wait_time);
	}
	if (wait_time == 0)
	{
		EntityConstructor::spawnExplosion(entity->getComponent<PositionComponent>()->position);
		
		for (auto& bars : Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerBar))
			bars->getComponent<InfoBar>()->setTimeUntilEgg(wait_time);
		
		fps_until_sec = 0, wait_time = -1;
	}
	// sa nu facem kill-urile chiar cand apare animatia..
	if (wait_time == -1)
		if (fps_until_sec == 12)
		{
			PositionComponent* position = entity->getComponent<PositionComponent>();
			
			bool bad_placed_egg = dynamic_col->verifyExplosionCollisionManager(position->position.x, position->position.y);
			if (bad_placed_egg)
			{
				GameInfoStorage::ScoreSub(3);
				for (auto& bars : Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerBar))
					bars->getComponent<InfoBar>()->scoreUpdate();
			}
			
			entity->destroy();
			ChickenAttack::setEgg(nullptr);
		}
}