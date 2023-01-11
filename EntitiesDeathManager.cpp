#include "EntitiesDeathManager.h"
#include "PositionComponent.h"
#include "EntityConstructor.h"
#include "InfoBar.h"
#include "Layering.h"
#include "ScenesManager.h"

void EntitiesDeathManager::playerDeath(Entity* entity)
{
	auto* enemyPosition = entity->getComponent<PositionComponent>();
	enemyPosition->position = EntityConstructor::player_spawn_position;
	EntityConstructor::PlayerLives--;
	Layers::getEntityfromLayer(Layers::scenGame, (int)Layers::game_layers::layerBar, 0)->getComponent<InfoBar>()->playerDeath();
	if (EntityConstructor::PlayerLives == 0)
	{
		cout << "Ai pierdut fraiere!" << endl;
		ScenesManager::showGameOver_Screen();
	}
}

void EntitiesDeathManager::enemyDeath(Entity* entity)
{
	entity->destroy();
	
	// Cand toti inamicii sunt morti spawnam oul magic!
	// Facem asa pentru ca entitaea fa fi stersa din lista la urmatorul update din ECS System
	if (Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerEnemy).size() == 1 && Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerEnemy).at(0)->isActive() == false)
		EntityConstructor::spawnGoldenEgg(EntityConstructor::golden_egg_spawn_position);
}