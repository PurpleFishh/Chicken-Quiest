#include "MouseCollision.h"
#include "../../Utils/CollisionUtils/CollisionUtils.h"
#include "../../ElementsConstructors/ScenesManager.h"
#include "../../ElementsConstructors/MenuConstructor.h"
#include "../../Game.h"
#include "../../Layering/Layering.h"
#include "../../Managers/ErrorHandler/ErrorHandler.h"
#include "../../Map/Map.h"

void MouseCollision::init()
{
	try {
		position = entity->getComponent<PositionComponent>();
		if (!entity->hasComponent<PositionComponent>())		throw ErrorHandler(typeid(MouseCollision).name(), typeid(PositionComponent).name());
	}
	catch (ErrorHandler e) { position = &entity->addCompoent<PositionComponent>(); }
	catch (std::exception& ex) { cout << ex.what() << endl; }

	try {
		sprite = entity->getComponent<SpriteComponent>();
		if (!entity->hasComponent<SpriteComponent>())		throw ErrorHandler(typeid(MouseCollision).name(), typeid(SpriteComponent).name());
	}
	catch (ErrorHandler e) { sprite = &entity->addCompoent<SpriteComponent>(); }
	catch (std::exception& ex) { cout << ex.what() << endl; }
}

void MouseCollision::handleEvents()
{
	// Button hover
	if (Game::event.type == SDL_MOUSEMOTION)
	{
		int texture_id = sprite->getTexture_id();
		if (CollisionUtils::point_in_Rect(Game::mouse_pos.x, Game::mouse_pos.y, *position))
		{
			if (texture_id % 2 == 0)
				sprite->setTexture(Textures::textures_menu.at(texture_id + 1), texture_id + 1);
		}
		else
		{
			if (texture_id % 2 == 1)
				sprite->setTexture(Textures::textures_menu.at(texture_id - 1), texture_id - 1);
		}
	}
	// Button click
	if (Game::event.type == SDL_MOUSEBUTTONDOWN)
	{
		//dynamicCol.verifyEntityCollision(Game::mouse_pos.x, Game::mouse_pos.y, Layers::getLayer(Layers::scenMainMenu, (int)Layers::main_menu_layers::layerButtons));
		if (CollisionUtils::point_in_Rect(Game::mouse_pos.x, Game::mouse_pos.y, *position))
		{
			if (MenuConstructor::menu_entities_specialization[entity] == "start level")
			{
				ScenesManager::showLevels_Menu();
				return;
			}
			if (MenuConstructor::menu_entities_specialization[entity] == "exit")
			{
				Game::stopGame();
				return;
			}

			if (MenuConstructor::menu_entities_specialization[entity] == "exit level")
			{
				ScenesManager::popScen();
				ScenesManager::destroyShowingScen();
				ScenesManager::showMain_Menu();
				return;
			}
			if (MenuConstructor::menu_entities_specialization[entity] == "retry")
			{
				ScenesManager::popScen();
				std::string mapPath = Map::getMapPath();
				ScenesManager::destroyShowingScen();
				ScenesManager::startLevel(mapPath);
				return;
			}
			if (MenuConstructor::menu_entities_specialization[entity] == "back")
			{
				Layers::ScenesStack.pop();
				return;
			}
			std::string specialization = MenuConstructor::menu_entities_specialization[entity];
			char lastChar = *(specialization.end() - 1);
			specialization.pop_back();
			if (specialization == "level ")
			{
				ScenesManager::startLevel((std::string)lvlMapFormat + lastChar + (std::string)lvlMapType);
				return;
			}
		}
	}
}
