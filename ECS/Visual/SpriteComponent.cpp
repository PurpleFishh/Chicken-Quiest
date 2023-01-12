#include "SpriteComponent.h"
#include "../../ECS/Collision/DynamicCollisionComponent.h"
#include "../../Game.h"
#include "../../ECS/Camera/CameraTarget.h"
#include "../../Layering/Layering.h"
#include "../../ElementsConstructors/ScenesManager.h"
#include "../../Managers/ErrorHandler/ErrorHandler.h"

SpriteComponent::SpriteComponent(const char* textureFile)
{
	setTexture(textureFile);
}
SpriteComponent::SpriteComponent(SDL_Texture* texture)
{
	this->texture = texture;
}
SpriteComponent::SpriteComponent(SDL_Texture* texture, int texture_id) : SpriteComponent(texture)
{
	this->texture_id = texture_id;
}
SpriteComponent::SpriteComponent(SDL_Texture* texture, int src_width, int src_height) : SpriteComponent(texture)
{
	this->src_width = src_width;
	this->src_height = src_height;
}
SpriteComponent::SpriteComponent(SDL_Texture* texture, int src_width, int src_height, int texture_id) : SpriteComponent(texture, src_width, src_height)
{
	this->texture_id = texture_id;
}
SpriteComponent::SpriteComponent(SDL_Texture* texture, animations_type animations)
{
	setTexture(texture, animations);
}
SpriteComponent::SpriteComponent(SDL_Texture* texture, animations_type animations, int src_width, int src_height) : SpriteComponent(texture, animations)
{
	this->src_width = src_width;
	this->src_height = src_height;
}
SpriteComponent::SpriteComponent(SDL_Texture* texture, animations_type animations, void(*PlayOnceAfterPlay)(Entity* entity)) : SpriteComponent(texture, animations)
{
	this->PlayOnceAfterPlay = PlayOnceAfterPlay;
}

void SpriteComponent::setTexture(const char* textureFile)
{
	texture = TextureManager::LoadTexture(textureFile);
}
void SpriteComponent::setTexture(SDL_Texture* texture)
{
	this->texture = texture;
}
void SpriteComponent::setTexture(SDL_Texture* texture, int texture_id)
{
	setTexture(texture);
	this->texture_id = texture_id;
}
void SpriteComponent::setTexture(SDL_Texture* texture, animations_type animations)
{
	animated = true;
	this->animations = animations;
	this->texture = texture;
	playAnimation(animations.begin()->first);
}

void SpriteComponent::init()
{
	try {
		posdetails = entity->getComponent<PositionComponent>();
		if (!entity->hasComponent<PositionComponent>())		throw ErrorHandler(typeid(SpriteComponent).name(), typeid(PositionComponent).name());
	}
	catch (ErrorHandler e) { posdetails = &entity->addCompoent<PositionComponent>(); }
	catch (std::exception& ex) { cout << ex.what() << endl; }

	srcRect.x = srcRect.y = 0;
	if (src_width == 0 && src_height == 0)
	{
		srcRect.h = (int)(posdetails->height);
		srcRect.w = (int)(posdetails->width);
	}
	else
	{
		srcRect.h = src_height;
		srcRect.w = src_width;
	}
}

void SpriteComponent::update()
{
	// play the needed frame from the animation
	if (animated)
	{
		// Daca are doar un frame nu are rost sa tinem acest timer pentru animatie
		if (frames > 1)
			animation_timer++;

		int futureframe = srcRect.w * static_cast<int>((int)((animation_timer + 1) / (speed / delta_time)) % frames), oldy = srcRect.y;

		srcRect.x = srcRect.w * static_cast<int>((int)(animation_timer / (speed / delta_time)) % frames);
		srcRect.y = static_cast<int>(animation_row * posdetails->height * posdetails->scale);

		// Verificam daca s-a schimbat linia din sprite sheet sa resetam timerul sau s-a revenit la prima coloana
		if (oldy != srcRect.y)
			animation_timer = 0;
		if (srcRect.x != 0 && futureframe == 0)
		{
			animation_timer = 0;
			// Optiunea de a nu repeta animatia
			if (PlayOnceAfterPlay != nullptr)
			{
				(*PlayOnceAfterPlay)(entity);
				PlayOnceAfterPlay = nullptr;
			}
		}
	}

	destRect.x = (int)posdetails->position.x;
	destRect.y = (int)posdetails->position.y;

	// Verificam daca e entitatea care trebuie urmarita de camera
	if (ScenesManager::getShowingScen() == (int)Layers::scenGame)
		if (entity->getLayer_Id() != (int)Layers::game_layers::layerBar)
			if (entity->hasComponent<CameraTarget>())
			{
				destRect.x = (int)(destRect.x - (CameraTarget::camera.x));
				destRect.y = (int)(destRect.y - (CameraTarget::camera.y));
			}
			else
			{
				destRect.x = (int)(destRect.x - (CameraTarget::cameraOffset.x));
				destRect.y = (int)(destRect.y - (CameraTarget::cameraOffset.y));
			}

	destRect.h = (int)(posdetails->height * posdetails->scale);
	destRect.w = (int)(posdetails->width * posdetails->scale);
}

void SpriteComponent::playAnimation(std::string animationName)
{

	frames = animations[animationName].frames;
	animation_row = animations[animationName].row;
	speed = animations[animationName].speed;
}
void SpriteComponent::playAnimation(std::string animationName, void(*PlayOnceAfterPlay)(Entity* entity))
{
	playAnimation(animationName);
	this->PlayOnceAfterPlay = PlayOnceAfterPlay;
}

bool SpriteComponent::playingThisAnimation(std::string animationName)
{
	return animation_row == animations[animationName].row;
}

void SpriteComponent::draw()
{
	TextureManager::Draw(texture, srcRect, destRect, spriteFlip, entity->getLayer_Id() != (int)Layers::game_layers::layerBackground);
}


// Doamne Fereste...

//if (entity->hasComponent<CollisionComponent>() && entity->getComponent<CollisionComponent>()->getType() != "ground")
	//{
	//	//destRect.x += Game::cam_offset_x;
	//	//destRect.y += Game::cam_offset_y;
	//	SDL_Rect rectx = destRect;
	//	destRect.x = (int)posdetails->position.x;
	//	destRect.y = (int)posdetails->position.y;
	//	//int x = (int)posdetails->position.x, y = (int)posdetails->position.y;
	//	onGround = false;
	//	if (posdetails->velocity.x < 0)
	//	{
	//		auto tiles = Layers::layers[Layers::layerMap];

	//		if (tiles[(int)((destRect.y + 1) / 64) * Map::cols + (int)(destRect.x / 64)]->hasComponent<CollisionComponent>()
	//			|| tiles[(int)((destRect.y - 1 + destRect.h) / 64) * Map::cols + (int)(destRect.x / 64)]->hasComponent<CollisionComponent>())
	//		{
	//			cout << "xAre!" << posdetails->velocity << "\n";
	//			cout << "xAre!" << destRect.x << "\n";
	//			//destRect.x = colcoord.x + colcoord.w;
	//			//if ((!tiles[(int)(((destRect.y) + destRect.h) / 64) * Map::cols + (int)(destRect.x / 64)]->hasComponent<CollisionComponent>()
	//			//	&& !tiles[(int)(((destRect.y) + destRect.h) / 64) * Map::cols + (int)((destRect.x + destRect.w - 1) / 64)]->hasComponent<CollisionComponent>())
	//			//	&& (!tiles[(int)((destRect.y) / 64) * Map::cols + (int)(destRect.x / 64)]->hasComponent<CollisionComponent>()
	//			//		&& !tiles[(int)((destRect.y) / 64) * Map::cols + (int)((destRect.x + destRect.w - 1) / 64)]->hasComponent<CollisionComponent>()))
	//			{
	//				destRect.x = ((int)(destRect.x / 64) + 1) * 64;
	//				posdetails->velocity.x = 0;
	//			}
	//		}
	//	}
	//	else
	//		if (posdetails->velocity.x != 0)
	//		{
	//			auto tiles = Layers::layers[Layers::layerMap];

	//			if (tiles[(int)((destRect.y + 1) / 64) * Map::cols + ((int)((destRect.x + destRect.w) / 64))]->hasComponent<CollisionComponent>()
	//				|| tiles[(int)((destRect.y - 1 + destRect.h) / 64) * Map::cols + ((int)((destRect.x + destRect.w) / 64))]->hasComponent<CollisionComponent>())
	//			{
	//				//cout << "\nx1Are!" << tiles[(int)((destRect.y + 1) / 64) * Map::cols + ((int)((destRect.x + destRect.w) / 64))]->getComponent<CollisionComponent>()->colliderbox.x << "\n";
	//				//cout << "x1Are!" << destRect.x + destRect.w  - tiles[(int)((destRect.y + destRect.h) / 64) * Map::cols + ((int)((destRect.x + destRect.w) / 64))]->getComponent<CollisionComponent>()->colliderbox.x << "\n";
	//				cout << "xAre!" << destRect.x + destRect.w << "\n";
	//				cout << (round(((destRect.x + destRect.w) / 64))) << '\n';
	//				//destRect.x = colcoord.x + colcoord.w;
	//				///if (posdetails->velocity.y == 0)
	//				//{
	//				//if (posdetails->velocity.y == 0 || (!tiles[(int)(((destRect.y) + destRect.h) / 64) * Map::cols + (int)(destRect.x / 64)]->hasComponent<CollisionComponent>()
	//				//	&& !tiles[(int)(((destRect.y) + destRect.h) / 64) * Map::cols + (int)((destRect.x + destRect.w - 1) / 64)]->hasComponent<CollisionComponent>()))
	//					//&& (!tiles[(int)((destRect.y) / 64) * Map::cols + (int)(destRect.x / 64)]->hasComponent<CollisionComponent>()
	//					//	&& !tiles[(int)((destRect.y) / 64) * Map::cols + (int)((destRect.x + destRect.w - 1) / 64)]->hasComponent<CollisionComponent>()))
	//				//{	
	//					//destRect.x = tiles[(int)((destRect.y + destRect.h) / 64) * Map::cols + ((int)((destRect.x + destRect.w) / 64))]->getComponent<CollisionComponent>()->colliderbox.x - destRect.w;
	//				destRect.x = ((int)(destRect.x / 64) + 1) * 64 - destRect.w;
	//				//if (tiles[(int)((destRect.y - 1 + destRect.h) / 64) * Map::cols + ((int)((destRect.x + destRect.w) / 64))]->hasComponent<CollisionComponent>())
	//				//	destRect.x -= destRect.x + destRect.w - tiles[(int)((destRect.y - 1 + destRect.h) / 64) * Map::cols + ((int)((destRect.x + destRect.w) / 64))]->getComponent<CollisionComponent>()->colliderbox.x;
	//				//else
	//				//	if (tiles[(int)((destRect.y + 1) / 64) * Map::cols + ((int)((destRect.x + destRect.w) / 64))]->hasComponent<CollisionComponent>())
	//				//		destRect.x -= destRect.x + destRect.w - tiles[(int)((destRect.y + 1) / 64) * Map::cols + ((int)((destRect.x + destRect.w) / 64))]->getComponent<CollisionComponent>()->colliderbox.x;
	//				posdetails->velocity.x = 0;

	//				//}
	//			}
	//		}
	//	if (posdetails->velocity.y < 0)
	//	{
	//		auto tiles = Layers::layers[Layers::layerMap];

	//		if (tiles[(int)((destRect.y) / 64) * Map::cols + (int)(destRect.x / 64)]->hasComponent<CollisionComponent>()
	//			|| tiles[(int)((destRect.y) / 64) * Map::cols + (int)((destRect.x + destRect.w - 1) / 64)]->hasComponent<CollisionComponent>())
	//		{
	//			//cout << "yAre!" << tiles[(int)((destRect.y + 1) / 64) * Map::cols + (int)(destRect.x / 64)]->getComponent<CollisionComponent>()->colliderbox.y <<"\n";
	//			//cout << "yAre!" << destRect.y << "\n";
	//			//cout << "yAre!" << ((int)(destRect.y / 64) + 1) * 64 << "\n";
	//			//destRect.x = colcoord.x + colcoord.w;
	//			destRect.y = ((int)(destRect.y / 64) + 1) * 64;
	//			posdetails->velocity.y = 0;
	//			onGround = true;
	//			//posdetails->sign.y = 0;
	//		}
	//	}
	//	else
	//		if (posdetails->velocity.y != 0)
	//		{
	//			auto tiles = Layers::layers[Layers::layerMap];

	//			if (tiles[(int)(((destRect.y) + destRect.h) / 64) * Map::cols + (int)(destRect.x / 64)]->hasComponent<CollisionComponent>()
	//				|| tiles[(int)(((destRect.y) + destRect.h) / 64) * Map::cols + (int)((destRect.x + destRect.w - 1) / 64)]->hasComponent<CollisionComponent>())
	//			{
	//				//cout << "\ncollider y!" << tiles[(int)(((destRect.y + 1) + destRect.h) / 64) * Map::cols + (int)(destRect.x / 64)]->getComponent<CollisionComponent>()->colliderbox.y << "\n";
	//				//cout << "player y!" << destRect.y << "\n";
	//				//cout << "player setted y!" << ((int)(destRect.y / 64) + 1) * 64 << "\n";
	//				//cout << "Are!\n";
	//				//destRect.x = colcoord.x + colcoord.w;
	//				destRect.y = ((int)(destRect.y / 64) + 1) * 64 - destRect.h;
	//				//destRect.y = tiles[(int)(((destRect.y + 1) + destRect.h) / 64) * Map::cols + (int)(destRect.x / 64)]->getComponent<CollisionComponent>()->colliderbox.y - 64;
	//				posdetails->velocity.y = 0;
	//				onGround = true;
	//				//posdetails->sign.y = 0;
	//			}
	//		}

	//	/*for (auto& tile : Layers::layers[Layers::layerCollision])
	//	{
	//		auto colliderComp = tile->getComponent<CollisionComponent>();
	//		if (Collision::rectCollision(destRect, colliderComp->colliderbox))
	//		{
	//			auto collidercoord = colliderComp->colliderbox;
	//			int difx = destRect.x - collidercoord.x;
	//			int dify = destRect.y - collidercoord.y;
	//			if (abs(difx) <= abs(dify))
	//				destRect.x -= difx;
	//			else
	//				destRect.y -= dify;
	//			break;
	//		}
	//		/*f(Collision::rectCollision(rectx, colliderComp->colliderbox))
	//		{
	//			std::cout << "x collision " << entity->getComponent<CollisionComponent>()->getType() << " -> " << tile->getComponent<CollisionComponent>()->getType() << std::endl;
	//			//std::cout << "Player pos: " << entity->getComponent<PositionComponent>()->position << " -> " << tile->getComponent<CollisionComponent>()->posdetails->position << '\n';
	//			//std::cout << "Player pos: " << posdetails->position << '\n';
	//			std::cout << "(unde vrea)Player pos: " << posdetails->position << '\n';
	//			std::cout << "(unde e)Player pos: " << rectx.x << ", " << rectx.y << "->" << colliderComp->colliderbox.y << '\n';
	//			std::cout << "(collidere x)Player pos: " << entity->getComponent<CollisionComponent>()->colliderbox.x << " -> " << tile->getComponent<CollisionComponent>()->colliderbox.x << '\n';
	//			//std::cout << "Player pos: " << entity->getComponent<CollisionComponent>()->destRect.x << " -> " << tile->getComponent<CollisionComponent>()->destRect.x << '\n';
	//			std::cout << "Player pos: " << entity->getComponent<SpriteComponent>()->destRect.x << " -> " << tile->getComponent<SpriteComponent>()->destRect.x << '\n';
	//			//rectx.x = entity->getComponent<CollisionComponent>()->destRect.x;// +(Game::camera.x - Game::cam_offset_x);
	//			//colx = true;
	//			x = tile->getComponent<CollisionComponent>()->posdetails->position.x;
	//			if (posdetails->velocity.x > 0)//&& entity->getComponent<CollisionComponent>()->col == 0)
	//			{
	//				//x = tile->getComponent<CollisionComponent>()->posdetails->position.x;
	//				x -= rectx.w;
	//				//xxx = rectx.x;
	//				//entity->getComponent<CollisionComponent>()->col = 1;
	//			}
	//			else if (posdetails->velocity.x < 0)
	//			{
	//				x += colliderComp->colliderbox.w;
	//				//entity->getComponent<CollisionComponent>()->col = -1;
	//			}
	//			rectx.x = x;
	//			//destRect.x = x;

	//		}
	//		if (Collision::rectCollision(destRect, colliderComp->colliderbox))
	//		{
	//			std::cout << "yPlayer pos: " << entity->getComponent<CollisionComponent>()->colliderbox.y << " -> " << tile->getComponent<CollisionComponent>()->colliderbox.y << '\n';
	//			std::cout << "yPlayer pos: " << entity->getComponent<SpriteComponent>()->destRect.y << " -> " << tile->getComponent<SpriteComponent>()->destRect.y << '\n';
	//			y = tile->getComponent<CollisionComponent>()->posdetails->position.y;
	//			if (posdetails->velocity.y > 0)
	//			{
	//				y -= destRect.h;
	//				cout << "col on y+" << '\n';
	//			}
	//			else if (posdetails->velocity.y < 0)
	//			{
	//				y += colliderComp->colliderbox.h;
	//				cout << "col on y+" << '\n';
	//			}
	//			//rectx.x = x;
	//			destRect.y = y;
	//		}*/

	//	posdetails->position.x = destRect.x;
	//	posdetails->position.y = destRect.y;
	//	//destRect.x = x;
	//	//destRect.y = y;

	//	//std::cout << "x collision " << entity->getComponent<CollisionComponent>()->getType() << std::endl;

	//	//std::cout << "Player pos: " << entity->getComponent<CollisionComponent>()->colliderbox.x << '\n';
	//	//std::cout << "Player pos: " << entity->getComponent<CollisionComponent>()->destRect.x<< '\n';
	//	//std::cout << "Player pos: " << entity->getComponent<SpriteComponent>()->destRect.x << '\n';
	//	destRect.x = destRect.x - Game::camera.x;// +(Game::camera.x - Game::cam_offset_x);
	//	destRect.y = destRect.y - Game::camera.y;// +(Game::camera.y - Game::cam_offset_y);
//
	//}
	//else
	//cout << "Sprite\n";