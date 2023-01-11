#include "EntityConstructor.h"
#include "EntitiesDeathManager.h"
#include "Components.h"
#include "Layering.h"
#include "ScenesManager.h"
#include "Map.h"

extern System ECS_Manager;
Vector2D EntityConstructor::player_spawn_position(0, 0);
Vector2D EntityConstructor::golden_egg_spawn_position(0, 0);
bool EntityConstructor::PlayerWon = false;
short EntityConstructor::PlayerLives = 0;
Entity& EntityConstructor::emptyTile = ECS_Manager.addEntity();

Entity& EntityConstructor::spawnPlayer(const Vector2D& spawn_position)
{
	auto& player = ECS_Manager.addEntity();
	player.addCompoent<PositionComponent>(spawn_position.x, spawn_position.y, PLAYER_H, PLAYER_W, 1.0f, 1.f, true);
	player.addCompoent<DynamicCollisionComponent>();
	player.addCompoent<SpriteComponent>(Textures::animations_textures.at(0), Textures::animations.at(0));
	player.addCompoent<KeyboardControllerComponent>();
	player.addCompoent<CollisionComponent>("player");
	player.addCompoent<CameraTarget>();
	Layers::add(Layers::scenGame, &player, (int)Layers::game_layers::layerPlayer);
	PlayerLives = 5 - Map::difficulty < 1 ? 1 : 5 - Map::difficulty;

	return player;
}

Entity& EntityConstructor::spawnEnemy(const Vector2D& spawn_position)
{
	auto& enemy = ECS_Manager.addEntity();
	enemy.addCompoent<PositionComponent>(spawn_position.x, spawn_position.y, ENEMY_H, ENEMY_W, 0.3f + Map::difficulty / 10., 1.f, true);
	enemy.addCompoent<DynamicCollisionComponent>();
	enemy.addCompoent<SpriteComponent>(Textures::animations_textures.at(1), Textures::animations.at(1));
	enemy.addCompoent<AiBehaviour>(1);
	enemy.addCompoent<CollisionComponent>("enemy");
	Layers::add(Layers::scenGame, &enemy, (int)Layers::game_layers::layerEnemy);

	return enemy;
}

Entity& EntityConstructor::spawnEgg(const Vector2D& spawn_position)
{
	auto& egg = ECS_Manager.addEntity();
	egg.addCompoent<PositionComponent>(spawn_position.x, spawn_position.y, EGG_H, EGG_W, 1.2f, 1.f, true);
	egg.addCompoent<DynamicCollisionComponent>();
	egg.addCompoent<EggBoom>(3);
	egg.addCompoent<SpriteComponent>(Textures::textures.at(10));
	egg.addCompoent<CollisionComponent>("egg");
	Layers::add(Layers::scenGame, &egg, (int)Layers::game_layers::layerEggs);

	return egg;
}
Entity& EntityConstructor::spawnGoldenEgg(const Vector2D& spawn_position)
{
	auto& golden_egg = ECS_Manager.addEntity();
	golden_egg.addCompoent<PositionComponent>(spawn_position.x, spawn_position.y + 16, 48, 44);
	golden_egg.addCompoent<SpriteComponent>(Textures::textures.at(11));
	golden_egg.addCompoent<CollisionComponent>("golden_egg");
	Layers::add(Layers::scenGame, &golden_egg, (int)Layers::game_layers::layerGoldenEggs);

	return golden_egg;
}

Entity& EntityConstructor::spawnExplosion(const Vector2D& spawn_position)
{
	auto& explostion = ECS_Manager.addEntity();
	explostion.addCompoent<PositionComponent>(spawn_position.x - EXPLOSION_W / 2, spawn_position.y - EXPLOSION_H / 2, EXPLOSION_H, EXPLOSION_W);
	explostion.addCompoent<SpriteComponent>(Textures::animations_textures.at(2), Textures::animations.at(2), &AnimationAfter_destroyEntity);
	Layers::add(Layers::scenGame, &explostion, (int)Layers::game_layers::layerExplosion);

	return explostion;
}
Entity& EntityConstructor::spawnBackground(int scen, int layer, const Vector2D& spawn_position, SDL_Texture* texture, int w, int h, int scrw, int scrh)
{
	auto& sky = ECS_Manager.addEntity();
	sky.addCompoent<PositionComponent>(spawn_position.x, spawn_position.y, h, w);
	sky.addCompoent<SpriteComponent>(texture, scrw, scrh);
	Layers::add(scen, &sky, layer);

	return sky;
}
Entity& EntityConstructor::spawnText(const Vector2D& spawn_position, std::string text)
{
	auto& textEntity = ECS_Manager.addEntity();
	textEntity.addCompoent<PositionComponent>(spawn_position.x, spawn_position.y);
	textEntity.addCompoent<TextComponent>(text, SDL_Color{ 255, 255, 255 });
	Layers::add(Layers::scenGame, &textEntity, (int)Layers::game_layers::layerBar);

	return textEntity;
}
Entity& EntityConstructor::spawnInfoBar(const Vector2D& spawn_position, SDL_Color color)
{
	auto& textEntity = ECS_Manager.addEntity();
	textEntity.addCompoent<PositionComponent>(spawn_position.x, spawn_position.y);
	textEntity.addCompoent<InfoBar>(" ", color);
	Layers::add(Layers::scenGame, &textEntity, (int)Layers::game_layers::layerBar);

	return textEntity;
}

void EntityConstructor::AnimationAfter_destroyEntity(Entity* entity)
{
	entity->destroy();
}
void EntityConstructor::AnimationAfter_playerWin(Entity* entity)
{
	/*cout << "Win!" << endl;
	EntitiesDeathManager::playerDeath(entity);
	entity->getComponent<SpriteComponent>()->playAnimation("Idle");
	entity->getComponent<KeyboardControllerComponent>()->able_to_move = true;*/
	ScenesManager::showWin_Screen();
	PlayerWon = false;
}
