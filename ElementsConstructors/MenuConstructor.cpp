#include "MenuConstructor.h"
#include "../ECS/Components.h"
#include "../Layering/Layering.h"

extern System ECS_Manager;
std::map<Entity*, std::string> MenuConstructor::menu_entities_specialization;

Entity& MenuConstructor::spawnButton(int scen, int layer, const Vector2D& spawn_position, std::string specialization, int texture_id, int w, int h, int scrw, int scrh)
{
	auto& button = ECS_Manager.addEntity();
	button.addCompoent<PositionComponent>(spawn_position.x, spawn_position.y, h, w);
	button.addCompoent<SpriteComponent>(Textures::textures_menu.at(texture_id), scrw, scrh, texture_id);
	button.addCompoent<MouseCollision>();
	Layers::add(scen, &button, layer);
	menu_entities_specialization[&button] = specialization;

	return button;
}
