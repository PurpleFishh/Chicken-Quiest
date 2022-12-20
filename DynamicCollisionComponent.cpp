#include "DynamicCollisionComponent.h"
#include "Layering.h"
#include "Map.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "AiBehaviour.h"


void DynamicCollisionComponent::init()
{
	SpriteComponent::init();
	// Gravity
	posdetails->sign.y = 1;
}

void DynamicCollisionComponent::setNewPosition()
{
	destRect.x = (int)posdetails->position.x;
	destRect.y = (int)posdetails->position.y;
	collisionX = collisionYcorner1 = collisionYcorner2 = false;

	if (borderCollision()) return;

	// BugFix: - Daca playerul era in cadere, se misca pe axa X si cadea intre doua tile-uri acesta era teleportat la marginea tile-ului din spate
	//		   - Folosim colX pentru a semnala daca a avut loc o coliziune pe axa X(folosim verificarea pentru coloziunile din cadere de exemplu de un perete)
	//         - Folosim in colziunea pe Y colX sa vedem daca colziunea a fost rezolvata cu ajutorul lui X sa nu ii mai schimbam pozitia dubios la player
	//         - Si apoi in final verificam iar coloziunea pe X pentru ca coloziunea cand acesta este pe o platforma(onGround)
	if (posdetails->velocity.x < 0)
	{
		// Alt Doamne fereste...

		// Verificam coliziuni pentru mers in stanga
		// Verificam daca exisata coliziunea in coltul din stanga sus si stanga jos al entitatii
		if (verifyTileCollision(destRect.x, destRect.y + 7) || verifyTileCollision(destRect.x, destRect.y + destRect.h - 2))
			if (!verifyTileCollision(destRect.x + destRect.w - 1, destRect.y + destRect.h + 2))
				if (!verifyTileCollision(destRect.x + destRect.w, destRect.y))
				{
					// Daca entitatea e in cadere
					if (!onGround)
					{
						destRect.x = ((int)(destRect.x / TILE_SIZE) + 1) * TILE_SIZE;
						//if (entity->hasComponent<AiBehaviour>())
						//	posdetails->sign.x *= -1;
						posdetails->velocity.x = 0;
						collisionX = true;
					}
				}
	}
	else
		if (posdetails->velocity.x != 0)
		{
			// Verificam coliziuni pentru mers in dreapta
			// Verificam daca exisata coliziunea in coltul din dreapta sus si dreapta jos al entitatii
			if (verifyTileCollision(destRect.x + destRect.w, destRect.y + 7) || verifyTileCollision(destRect.x + destRect.w, destRect.y + destRect.h - 2))
				if (!verifyTileCollision(destRect.x + 1, destRect.y + destRect.h))
					if (!verifyTileCollision(destRect.x, destRect.y))
					{
						// Daca entitatea e in cadere
						if (!onGround)
						{
							destRect.x = ((int)(destRect.x / TILE_SIZE) + 1) * TILE_SIZE - destRect.w;
							//if (entity->hasComponent<AiBehaviour>())
							//	posdetails->sign.x *= -1;
							posdetails->velocity.x = 0;
							collisionX = true;

						}
					}
		}
	onGround = false;
	// Verificam coliziuni pe y
	if (posdetails->velocity.y < 0)
	{
		// Verificam coliziuni pentru mers in sus
		// Verificam daca exisata coliziunea in coltul din stanga sus si dreapta sus al entitatii
		if (verifyTileCollision(destRect.x, destRect.y) || verifyTileCollision(destRect.x + destRect.w - 1, destRect.y))
		{
			//cout << "Coll y\n";
			// Daca a avut loc coliziune pe X il lasam in pace
			if (!collisionX)
			{
				destRect.y = ((int)(destRect.y / TILE_SIZE) + 1) * TILE_SIZE;
				posdetails->velocity.y = 0;
				// Oprim saltul si aplicam gravitata la loc(il facem sa coboare cand daca cu capul de colziune)
				posdetails->sign.y = 1;
				collisionYcorner1 = verifyTileCollision(destRect.x, destRect.y);
				collisionYcorner2 = verifyTileCollision(destRect.x + destRect.w - 1, destRect.y);
				//cout << "coll y1" << endl;
			}
		}
	}
	else
		if (posdetails->velocity.y != 0)
		{
			// Verificam coliziuni pentru mers in jos
			// Verificam daca exisata coliziunea in coltul din stanga jos si dreapta jos al entitatii
			if (verifyTileCollision(destRect.x, destRect.y + destRect.h) || verifyTileCollision(destRect.x + destRect.w - 1, destRect.y + destRect.h))
			{
				//cout << "Coll y\n";
				// Daca a avut loc coliziune pe X il lasam in pace
				if (!collisionX)
				{
					destRect.y = ((int)(destRect.y / TILE_SIZE) + 1) * TILE_SIZE - destRect.h;
					posdetails->velocity.y = 0;
					collisionYcorner1 = verifyTileCollision(destRect.x - 5, destRect.y + destRect.h);
					collisionYcorner2 = verifyTileCollision(destRect.x + destRect.w + 5, destRect.y + destRect.h);
					//cout << collisionYcorner1 << ' ' << collisionYcorner2 << endl;
					//cout << "coll y2" << endl;
				}
				onGround = true;
			}
		}

	// Verificam coliziuni pe x
	if (posdetails->velocity.x < 0)
	{
		// Verificam coliziuni pentru mers in stanga
		// Verificam daca exisata coliziunea in coltul din stanga sus si stanga jos al entitatii
		if (verifyTileCollision(destRect.x, destRect.y + 1) || verifyTileCollision(destRect.x, destRect.y - 1 + destRect.h))
		{
			// Verificam cand e deja pe pamant cu aceasta informatie actualizata deja mai sus
			if (onGround)
			{
				destRect.x = ((int)(destRect.x / TILE_SIZE) + 1) * TILE_SIZE;
				//if (entity->hasComponent<AiBehaviour>())
				//	posdetails->sign.x *= -1;
				posdetails->velocity.x = 0;
				collisionX = true;
			}
		}
	}
	else
		if (posdetails->velocity.x != 0)
		{
			// Verificam coliziuni pentru mers in dreapta
			// Verificam daca exisata coliziunea in coltul din dreapta sus si dreapta jos al entitatii
			if (verifyTileCollision(destRect.x + destRect.w, destRect.y + 1) || verifyTileCollision(destRect.x + destRect.w, destRect.y - 1 + destRect.h))
			{
				// Verificam cand e deja pe pamant cu aceasta informatie actualizata deja mai sus
				if (onGround)
				{
					destRect.x = ((int)(destRect.x / TILE_SIZE) + 1) * TILE_SIZE - destRect.w;
					//if (entity->hasComponent<AiBehaviour>())
					//	posdetails->sign.x *= -1;
					posdetails->velocity.x = 0;
					collisionX = true;
					//cout << "coll x2" << endl;
				}
			}
		}

	// Actualizam pozitia entitatii caci posibil aceasta a fost modificata
	posdetails->position.x = destRect.x;
	posdetails->position.y = destRect.y;
}
void DynamicCollisionComponent::solveCollision(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2)
{
	if (collsioncornerX1)
	{
		destRect.x = ((int)(destRect.x / tileW) + 1) * tileW;
		posdetails->velocity.x = 0;
	}
	if (collsioncornerX2)
	{
		destRect.x = ((int)(destRect.x / tileW) + 1) * tileW - destRect.w;
		posdetails->velocity.x = 0;
	}
	if (collsioncornerY1)
	{
		destRect.y = ((int)(destRect.y / tileH) + 1) * tileH;
		posdetails->velocity.y = 0;
		posdetails->sign.y = 1;
	}
	if (collsioncornerY2)
	{
		destRect.y = ((int)(destRect.y / tileH) + 1) * tileH - destRect.h;
		posdetails->velocity.y = 0;
	}
}


bool DynamicCollisionComponent::verifyTileCollision(int x, int y)
{
	auto& tiles = Layers::getLayer(Layers::layerMap);

	return tiles[(int)(y / TILE_SIZE) * Map::cols + (int)(x / TILE_SIZE)]->hasComponent<CollisionComponent>();
}

bool  DynamicCollisionComponent::borderCollision()
{
	if (destRect.x < 0)
	{
		destRect.x = 0;
		posdetails->position.x = 0;
		posdetails->velocity.x = 0;
		
		collisionX = true;
	}
	if (destRect.y < 0)
	{
		destRect.y = 0;
		posdetails->position.y = 0;
		posdetails->sign.y = 1;

		collisionYcorner1 = true;
	}
	if (destRect.x + destRect.w > Map::cols * TILE_SIZE)
	{
		destRect.x = Map::cols * TILE_SIZE - destRect.w;
		posdetails->position.x = Map::cols * TILE_SIZE - destRect.w;
		posdetails->velocity.x = 0;

		collisionX = true;
	}
	if (destRect.y + destRect.h > Map::rows * TILE_SIZE)
	{
		destRect.y = Map::rows * TILE_SIZE - destRect.h;
		posdetails->position.y = Map::rows * TILE_SIZE - destRect.h;

		collisionYcorner2 = true;
	}

	return collisionX || collisionYcorner1 || collisionYcorner2;
}