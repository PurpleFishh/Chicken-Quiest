#include "AiBehaviour.h"
#include "../../Managers/ErrorHandler/ErrorHandler.h"


AiBehaviour::AiBehaviour(int movementDirection)
{
	this->movementDirection = movementDirection;
}

void AiBehaviour::init()
{
	try {
		position = entity->getComponent<PositionComponent>();
		if (!entity->hasComponent<PositionComponent>())		throw ErrorHandler(typeid(AiBehaviour).name(), typeid(PositionComponent).name());
	}
	catch (ErrorHandler e) { position = &entity->addCompoent<PositionComponent>(); }
	catch (std::exception& ex) { cout << ex.what() << endl; }
	
	try {
		dynamiccol = entity->getComponent<DynamicCollisionComponent>();
		if (!entity->hasComponent<DynamicCollisionComponent>())		throw ErrorHandler(typeid(AiBehaviour).name(), typeid(DynamicCollisionComponent).name());
	}
	catch (ErrorHandler e) { dynamiccol = &entity->addCompoent<DynamicCollisionComponent>(); }
	catch (std::exception& ex) { cout << ex.what() << endl; }
	
	try {
		sprite = entity->getComponent<SpriteComponent>();
		if (!entity->hasComponent<SpriteComponent>())		throw ErrorHandler(typeid(AiBehaviour).name(), typeid(SpriteComponent).name());
	}
	catch (ErrorHandler e) { sprite = &entity->addCompoent<SpriteComponent>(); }
	catch (std::exception& ex) { cout << ex.what() << endl; }

	position->sign.x = (float)movementDirection;
	if (sprite->isAnimated() && (float)movementDirection == -1)
		sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
}

void AiBehaviour::update()
{
	AImovement();
}

void AiBehaviour::AImovement()
{
	// Ajuns la marginea din dreapta, il intoarcem
	if (dynamiccol->collisionYcorner1 && !dynamiccol->collisionYcorner2)
	{
		position->sign.x = -1;
		position->velocity.x = 0;
		if (sprite->isAnimated())
			sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
	}
	// Ajuns la marginea din stanga, il intoarcem
	else if (dynamiccol->collisionYcorner2 && !dynamiccol->collisionYcorner1)
	{
		position->sign.x = 1;
		position->velocity.x = 0;
		if (sprite->isAnimated())
			sprite->spriteFlip = SDL_FLIP_NONE;
	}
	else
		// Coliziune cu un block, il trimitem in cealalta directie
		if (dynamiccol->collisionXcorner1 || dynamiccol->collisionXcorner2)
		{
			position->sign.x *= -1;
			if (sprite->isAnimated())
				sprite->spriteFlip = sprite->spriteFlip == SDL_FLIP_HORIZONTAL ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
		}
}