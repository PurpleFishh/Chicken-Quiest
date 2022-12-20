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

	//if (type == "ground")
	//{
	//	colliderbox.x += Game::camera.x;
	//	colliderbox.y += Game::camera.y;
	//}
	if(type != "ground")
	{
		colliderbox.x = posdetails->position.x;
		colliderbox.y = posdetails->position.y;
		colliderbox.w = posdetails->width * posdetails->scale;
		colliderbox.h = posdetails->height * posdetails->scale;
	}
	
	//if (type != "player")
	//{
	//colliderbox.x = colliderbox.x - (Game::camera.x + Game::cam_offset_x);
	//colliderbox.y = colliderbox.y - (Game::camera.y + Game::cam_offset_y);
	//if (type == "player")
	//{
	//	colliderbox.x = entity->getComponent<SpriteComponent>()->destRect.x;
	//	colliderbox.y = entity->getComponent<SpriteComponent>()->destRect.y;
	//}
	//destRect.x = colliderbox.x;
	//destRect.y = colliderbox.y;
	//}
	//else
	//{
	//	destRect.x = colliderbox.x - (Game::camera.x + (Game::camera.x - Game::cam_offset_x));
	//	destRect.y = colliderbox.y - (Game::camera.y + (Game::camera.y - Game::cam_offset_y));

		//colliderbox.x = colliderbox.x - (Game::camera.x + (Game::camera.x - Game::cam_offset_x));
		//colliderbox.y = colliderbox.y - (Game::camera.y + (Game::camera.y - Game::cam_offset_y));
	//}
}

void CollisionComponent::draw()
{
	SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
	//destRect = colliderbox;
	/*destRect.x -= Game::camera.x;
	destRect.y -= Game::camera.y;
	if (type != "player")
	{
		destRect.x -= Game::cam_offset_x;
		destRect.y -= Game::cam_offset_y;
	}*/
	/*if (type == "ground")
	{
		destRect.x -= Game::cam_offset_x;
		destRect.y -= Game::cam_offset_y;
	}*/
	SDL_RenderDrawRect(Game::renderer, &destRect);
}