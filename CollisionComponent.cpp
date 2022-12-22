#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "Game.h"


CollisionComponent::CollisionComponent(std::string type)
{
	this->type = type;
}

CollisionComponent::CollisionComponent(int x, int y, int w, int h, std::string type)
{
	colliderbox.x = x;
	colliderbox.y = y;
	colliderbox.w = w;
	colliderbox.h = h;
	this->type = type;
}
std::string CollisionComponent::getType()
{
	return type;
}

void CollisionComponent::init()
{
	if (!entity->hasComponent<PositionComponent>())
		entity->addCompoent<PositionComponent>();
	posdetails = entity->getComponent<PositionComponent>();

	//if (type == "player")
	//colliderbox = entity->getComponent<SpriteComponent>()->destRect;

	colliderbox.x = posdetails->position.x;
	colliderbox.y = posdetails->position.y;
	colliderbox.w = posdetails->width * posdetails->scale;
	colliderbox.h = posdetails->height * posdetails->scale;

	destRect = colliderbox;
	//texture = ...
}

void CollisionComponent::update()
{
	destRect = entity->getComponent<SpriteComponent>()->destRect;

	if(type != "ground")
	{
		colliderbox.x = posdetails->position.x;
		colliderbox.y = posdetails->position.y;
		colliderbox.w = posdetails->width * posdetails->scale;
		colliderbox.h = posdetails->height * posdetails->scale;
	}
}

void CollisionComponent::draw()
{
	SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(Game::renderer, &destRect);
}