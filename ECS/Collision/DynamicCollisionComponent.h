#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "SDL_image.h"

/**
* @class DynamicCollisionComponent
* @brief Component that handles the collision of the entity that can move
*/
class DynamicCollisionComponent : public Component
{
private:
	/// <summary>
	/// Pointer to the PositionComponent of the entity (dependency)
	/// </summary>
	PositionComponent* position;
	
	/**
	* @brief Verify if the entity collides with a tile
	* @param x X position of the entity
	* @param y Y position of the entity
	* @param what_is_verified List of entities that will be verified
	* @return True if the entity collides with a tile
	*/
	bool verifyTileCollision(float x, float y, const vector<Entity*>& what_is_verified);
	/**
	* @brief Verify if the entity collides with the border of the map
	* @return True if the entity collides with the border of the map
	*/
	bool borderCollision();

	/**
	* @brief Solve the collision of the entity with a collidible tile
	* @param tileW Width of the tile
	* @param tileH Height of the tile
	* @param collsioncornerX1 True if the entity has collision on the left side
	* @param collsioncornerX2 True if the entity has collision on the right side
	* @param collsioncornerY1 True if the entity has collision on the top side 
	* @param collsioncornerY2 True if the entity has collision on the bottom side
	*/
	void solveCollision(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2);
	/**
	* @brief Solve the collision of the player with the enemies
	* @param tileW Width of the entity
	* @param tileH Height of the entity
	* @param collsioncornerX1 True if the entity has collision on the left side
	* @param collsioncornerX2 True if the entity has collision on the right side
	* @param collsioncornerY1 True if the entity has collision on the top side
	* @param collsioncornerY2 True if the entity has collision on the bottom side
	*/
	void enemyHit(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2);
<<<<<<< Updated upstream:DynamicCollisionComponent.h
	bool verifyExplosionCollision(const vector<Entity*>& list_of_entities, float x, float y, void(* solveCollision)(Entity* entity));
=======
	/**
	* @brief Verify if the entity collides with the explosion
	* @param list_of_entities List of entities that will be verified
	* @param x X position of the entity
	* @param y Y position of the entity
	* @param solveCollision Function that will be called if the entity collides with the explosion
	*/
	int verifyExplosionCollision(const vector<Entity*>& list_of_entities, float x, float y, void(* solveCollision)(Entity* entity));
	/**
	* @brief If the player collides with the winning egg
	* @param tileW Width of the entity
	* @param tileH Height of the entity
	* @param collsioncornerX1 True if the entity has collision on the left side
	* @param collsioncornerX2 True if the entity has collision on the right side
	* @param collsioncornerY1 True if the entity has collision on the top side
	* @param collsioncornerY2 True if the entity has collision on the bottom side
	*/
>>>>>>> Stashed changes:ECS/Collision/DynamicCollisionComponent.h
	void playerWin(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2);

	/**
	* @brief Solve the collisions using overlay method
	* @param tileW Width of the entity
	* @param tileH Height of the entity
	* @param collsioncornerX1 True if the entity has collision on the left side
	* @param collsioncornerX2 True if the entity has collision on the right side
	* @param collsioncornerY1 True if the entity has collision on the top side
	* @param collsioncornerY2 True if the entity has collision on the bottom side
	*/
	void SolveCollisionOverlay(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2);
public:
	/// <summary>
	/// onGround - if the entity is on the ground, isFalling - if the entity is falling
	/// </summary>
	bool onGround = false, isFalling = false;
	/// <summary>
	/// collisionXcorner1 - if the entity has collision on the left side, collisionXcorner2 - if the entity has collision on the right side
	/// collisionYcorner1 - if the entity has collision on the top side, collisionYcorner2 - if the entity has collision on the bottom side
	/// </summary>
	bool collisionXcorner1 = false, collisionXcorner2 = false, collisionYcorner1 = false, collisionYcorner2 = false;

	void init() override;
	void update() override;
	
	/**
	* @brief The function that manages the collisions, just give the entity that it will verify collision with, the verify function and the solve function
	* @param onGorundFlagModify True if the onGround flag will be modified
	* @param CollsionFlagsModify True if the collision flags will be modified
	* @param what_is_verified List of entities that will be verified
	* @param verifier Function that will be called to verify the collision
	* @param solver Function that will be called to solve the collision
	*/
	void collsionManager(bool onGorundFlagModify, bool CollsionFlagsModify, const vector<Entity*>& what_is_verified,bool (DynamicCollisionComponent::* verifier)(float x, float y, const vector<Entity*>& what_is_verified), void(DynamicCollisionComponent::* solver)(int tileW, int tileH, bool collsioncornerX1, bool collsioncornerX2, bool collsioncornerY1, bool collsioncornerY2));
	/**
	* @brief Verify if the entity collides with the explosion
	* @param x X position of the entity
	* @param y Y position of the entity
	* @return True if the entity collides with the explosion
	*/
	bool verifyExplosionCollisionManager(float x, float y);
	/**
	* @brief Verify if the entity collides with other entities
	* @param x X position of the entity
	* @param y Y position of the entity
	* @param what_is_verified List of entities that will be verified
	* @return True if the entity collides with other entities
	*/
	bool verifyEntityCollision(float x, float y, const vector<Entity*>& what_is_verified);
};

