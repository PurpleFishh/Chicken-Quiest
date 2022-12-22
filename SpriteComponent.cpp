#include "SpriteComponent.h"
#include "Collision.h"
#include "Game.h"
#include "Map.h"
#include "CollisionComponent.h"
#include "DynamicCollisionComponent.h"
#include "CameraTarget.h"

SpriteComponent::SpriteComponent(const char* textureFile)
{
	setTexture(textureFile);
}
SpriteComponent::SpriteComponent(SDL_Texture* texture)
{
	this->texture = texture;
}

//SpriteComponent::~SpriteComponent()
//{
//	SDL_DestroyTexture(texture);
//}

void SpriteComponent::setTexture(const char* textureFile)
{
	texture = TextureManager::LoadTexture(textureFile);
}
void SpriteComponent::setTexture(SDL_Texture* texture)
{
	this->texture = texture;
}

void SpriteComponent::init()
{
	posdetails = entity->getComponent<PositionComponent>();

	srcRect.x = srcRect.y = 0;
	srcRect.h = posdetails->height * posdetails->scale;
	srcRect.w = posdetails->width * posdetails->scale;
}

// Virtual cu DynamicColl care poate actiualiza destRect cu o poz fara coliziune
void SpriteComponent::setNewPosition()
{
	
}

void SpriteComponent::update()
{
	//setNewPosition();
	destRect.x = (int)posdetails->position.x;
	destRect.y = (int)posdetails->position.y;
	
	
	// Verificam daca e entitatea care trebuie urmarita de camera
	if (entity->hasComponent<CameraTarget>())
	{
		cout << posdetails->position << endl;
		destRect.x = destRect.x - (CameraTarget::camera.x);
		destRect.y = destRect.y - (CameraTarget::camera.y);
	}
	else
	{
		destRect.x = destRect.x - (CameraTarget::cameraOffset.x);
		destRect.y = destRect.y - (CameraTarget::cameraOffset.y);
	}

	destRect.h = posdetails->height * posdetails->scale;
	destRect.w = posdetails->width * posdetails->scale;
}

void SpriteComponent::draw()
{
	TextureManager::Draw(texture, srcRect, destRect);
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