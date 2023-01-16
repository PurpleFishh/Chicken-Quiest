#include "EntitiesDeathManager.h"
#include "../../ECS/Movement/PositionComponent.h"
#include "../../ElementsConstructors/EntityConstructor.h"
#include "../../ECS/Visual/InfoBar.h"
#include "../../Layering/Layering.h"
#include "../../ElementsConstructors/ScenesManager.h"
#include "../../Utils/InfoStorage/GameInfoStorage.h"

void EntitiesDeathManager::playerDeath(Entity* entity)
{
	auto* enemyPosition = entity->getComponent<PositionComponent>();
	enemyPosition->position = EntityConstructor::player_spawn_position;
	GameInfoStorage::PlayerLives--;
	GameInfoStorage::ScoreSub(10);
	for (auto& bars : Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerBar))
		bars->getComponent<InfoBar>()->playerDeath();
	//Layers::getEntityfromLayer(Layers::scenGame, (int)Layers::game_layers::layerBar, 0)->getComponent<InfoBar>()->playerDeath();
	if (GameInfoStorage::PlayerLives == 0)
		ScenesManager::showGameOver_Screen();
}

void EntitiesDeathManager::enemyDeath(Entity* entity)
{
	entity->destroy();
	GameInfoStorage::EnemiesAlive--;
	GameInfoStorage::ScoreAdd(5);
	for (auto& bars : Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerBar))
		bars->getComponent<InfoBar>()->enemyDeath();
	// Cand toti inamicii sunt morti spawnam oul magic!
	// Facem asa pentru ca entitaea fa fi stersa din lista la urmatorul update din ECS System
	if (Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerEnemy).size() == 1 && Layers::getLayer(Layers::scenGame, (int)Layers::game_layers::layerEnemy).at(0)->isActive() == false)
		EntityConstructor::spawnGoldenEgg(EntityConstructor::golden_egg_spawn_position);
}