#include "CollisionComponent.h"
#include "../../ECS/Visual/SpriteComponent.h"
#include "../../Game.h"
#include "../../Managers/ErrorHandler/ErrorHandler.h"


CollisionComponent::CollisionComponent(std::string type)
{
	this->type = type;
}
std::string CollisionComponent::getType()
{
	return type;
}

void CollisionComponent::init()
{
	try {
		sprite = entity->getComponent<SpriteComponent>();
		if (!entity->hasComponent<SpriteComponent>())		throw ErrorHandler(typeid(CollisionComponent).name(), typeid(SpriteComponent).name());
	}
	catch (ErrorHandler e) { sprite = &entity->addCompoent<SpriteComponent>(); }
	catch (std::exception& ex) { cout << ex.what() << endl; }
}
void CollisionComponent::draw()
{
	SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(Game::renderer, &sprite->destRect);
}