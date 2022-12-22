#include "DynamicCollisionComponent.h"
#include "Layering.h"
#include "Map.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "AiBehaviour.h"


void DynamicCollisionComponent::init()
{
	PositionComponent::init();
	// Gravity
	PositionComponent& pos = entity->addCompoent<PositionComponent>();
	position = pos.position;
	velocity = pos.velocity;
	sign = pos.sign;
	height = pos.height;
	width = pos.width;
	
	sign.y = 1;
}

void DynamicCollisionComponent::setNewPosition()
{
	velocity = getPotentialVelocity();
	position = getPotentialPosition();
	/*cout << position << endl;
	cout << velocity << endl;
	cout << sign << endl;
	cout << height << width << endl;*/
	collisionXcorner1 = collisionXcorner2 = collisionYcorner1 = collisionYcorner2 = false;

	if (borderCollision()) return;

	// BugFix: - Daca playerul era in cadere, se misca pe axa X si cadea intre doua tile-uri acesta era teleportat la marginea tile-ului din spate
	//		   - Folosim colX pentru a semnala daca a avut loc o coliziune pe axa X(folosim verificarea pentru coloziunile din cadere de exemplu de un perete)
	//         - Folosim in colziunea pe Y colX sa vedem daca colziunea a fost rezolvata cu ajutorul lui X sa nu ii mai schimbam pozitia dubios la player
	//         - Si apoi in final verificam iar coloziunea pe X pentru ca coloziunea cand acesta este pe o platforma(onGround)
	if (velocity.x < 0)
	{
		// Alt Doamne fereste...

		// Verificam coliziuni pentru mers in stanga
		// Verificam daca exisata coliziunea in coltul din stanga sus si stanga jos al entitatii
		if (verifyTileCollision(position.x, position.y + 7) || verifyTileCollision(position.x, position.y + height - 2))
			if (!verifyTileCollision(position.x + width - 1, position.y + height + 2))
				if (!verifyTileCollision(position.x + width, position.y))
				{
					// Daca entitatea e in cadere
					if (!onGround)
					{
						solveCollision(TILE_SIZE, TILE_SIZE, true, false, false, false);

						velocity.x = 0;
						collisionXcorner1 = true;
					}
				}
	}
	else
		if (velocity.x != 0)
		{
			// Verificam coliziuni pentru mers in dreapta
			// Verificam daca exisata coliziunea in coltul din dreapta sus si dreapta jos al entitatii
			if (verifyTileCollision(position.x + width, position.y + 7) || verifyTileCollision(position.x + width, position.y + height - 2))
				if (!verifyTileCollision(position.x + 1, position.y + height))
					if (!verifyTileCollision(position.x, position.y))
					{
						// Daca entitatea e in cadere
						if (!onGround)
						{
							solveCollision(TILE_SIZE, TILE_SIZE, false, true, false, false);

							velocity.x = 0;
							collisionXcorner2 = true;

						}
					}
		}
	onGround = false;
	// Verificam coliziuni pe y
	if (velocity.y < 0)
	{
		// Verificam coliziuni pentru mers in sus
		// Verificam daca exisata coliziunea in coltul din stanga sus si dreapta sus al entitatii
		if (verifyTileCollision(position.x, position.y) || verifyTileCollision(position.x + width - 1, position.y))
		{
			//cout << "Coll y\n";
			// Daca a avut loc coliziune pe X il lasam in pace
			if (!(collisionXcorner1 && collisionXcorner2))
			{
				solveCollision(TILE_SIZE, TILE_SIZE, false, false, true, false);

				collisionYcorner1 = verifyTileCollision(position.x, position.y);
				collisionYcorner2 = verifyTileCollision(position.x + width - 1, position.y);
				//cout << "coll y1" << endl;
			}
		}
	}
	else
		if (velocity.y != 0)
		{
			// Verificam coliziuni pentru mers in jos
			// Verificam daca exisata coliziunea in coltul din stanga jos si dreapta jos al entitatii
			if (verifyTileCollision(position.x + 1, position.y + height) || verifyTileCollision(position.x + width - 1, position.y + height))
			{
				//cout << "Coll y\n";
				// Daca a avut loc coliziune pe X il lasam in pace
				if (!(collisionXcorner1 && collisionXcorner2))
				{

					solveCollision(TILE_SIZE, TILE_SIZE, false, false, false, true);
					collisionYcorner1 = verifyTileCollision(position.x - 2, position.y + height);
					collisionYcorner2 = verifyTileCollision(position.x + width + 5, position.y + height);
					//if (entity->getLayer_Id() == 3)
					//	cout << collisionYcorner1 << ' ' << collisionYcorner2 << endl;
				}
				onGround = true;
			}
		}

	// Verificam coliziuni pe x
	if (velocity.x < 0)
	{
		// Verificam coliziuni pentru mers in stanga
		// Verificam daca exisata coliziunea in coltul din stanga sus si stanga jos al entitatii
		if (verifyTileCollision(position.x, position.y + 1) || verifyTileCollision(position.x, position.y - 1 + height))
		{
			// Verificam cand e deja pe pamant cu aceasta informatie actualizata deja mai sus
			if (onGround)
			{
				solveCollision(TILE_SIZE, TILE_SIZE, true, false, false, false);
				collisionXcorner1 = true;
			}
		}
	}
	else
		if (velocity.x != 0)
		{
			// Verificam coliziuni pentru mers in dreapta
			// Verificam daca exisata coliziunea in coltul din dreapta sus si dreapta jos al entitatii
			if (verifyTileCollision(position.x + width, position.y + 1) || verifyTileCollision(position.x + width, position.y - 1 + height))
			{
				// Verificam cand e deja pe pamant cu aceasta informatie actualizata deja mai sus
				if (onGround)
				{
					solveCollision(TILE_SIZE, TILE_SIZE, false, true, false, false);
					collisionXcorner2 = true;
					//cout << "coll x2" << endl;
				}
			}
		}
	// Actualizam pozitia entitatii caci posibil aceasta a fost modificata
}
void DynamicCollisionComponent::solveCollision(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2)
{
	if (collsioncornerX1)
	{
		position.x = ((int)(position.x / tileW) + 1) * tileW;
		//if (entity->getLayer_Id() == 3)
		//	cout << "1 " << destRect.x << endl;
		velocity.x = 0;
	}
	if (collsioncornerX2)
	{
		position.x = ((int)(position.x / tileW) + 1) * tileW - width;
		velocity.x = 0;
	}
	if (collsioncornerY1)
	{
		position.y = ((int)(position.y / tileH) + 1) * tileH;
		velocity.y = 0;
		// Oprim saltul si aplicam gravitata la loc(il facem sa coboare cand daca cu capul de colziune)
		sign.y = 1;
	}
	if (collsioncornerY2)
	{
		position.y = ((int)(position.y / tileH) + 1) * tileH - height;
		velocity.y = 0;
	}
	//if (entity->getLayer_Id() == 3)
	//	cout << "2 " << destRect.x << endl;
}


bool DynamicCollisionComponent::verifyTileCollision(int x, int y)
{
	auto& tiles = Layers::getLayer(Layers::layerMap);

	return tiles[(int)(y / TILE_SIZE) * Map::cols + (int)(x / TILE_SIZE)]->hasComponent<CollisionComponent>();
}

bool  DynamicCollisionComponent::borderCollision()
{
	if (position.x < 0)
	{
		position.x = 0;
		velocity.x = 0;

		collisionXcorner1 = true;
	}
	if (position.y < 0)
	{
		position.y = 0;
		sign.y = 1;

		collisionYcorner1 = true;
	}
	if (position.x + width > Map::cols * TILE_SIZE)
	{
		position.x = Map::cols * TILE_SIZE - width;
		velocity.x = 0;

		collisionXcorner2 = true;
	}
	if (position.y + height > Map::rows * TILE_SIZE)
	{
		position.y = Map::rows * TILE_SIZE - height;

		collisionYcorner2 = true;
	}

	return collisionXcorner1 || collisionXcorner2 || collisionYcorner1 || collisionYcorner2;
}