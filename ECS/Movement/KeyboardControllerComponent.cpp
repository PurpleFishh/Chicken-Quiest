#include "KeyboardControllerComponent.h"
#include "../../Game.h"
#include "../../ElementsConstructors/EntityConstructor.h"
#include "../../Utils/Eggs/ChickenAttack.h"
#include "../../Managers/ErrorHandler/ErrorHandler.h"
#include "../../Utils/InfoStorage/GameInfoStorage.h"

void KeyboardControllerComponent::init()
{
	try {
		position = entity->getComponent<PositionComponent>();
		if (!entity->hasComponent<PositionComponent>())		throw ErrorHandler(typeid(KeyboardControllerComponent).name(), typeid(PositionComponent).name());
	}
	catch (ErrorHandler e) { position = &entity->addCompoent<PositionComponent>(); }
	catch (std::exception& ex) { cout << ex.what() << endl; }
	
	try {
		sprite = entity->getComponent<SpriteComponent>();
		if (!entity->hasComponent<SpriteComponent>())		throw ErrorHandler(typeid(KeyboardControllerComponent).name(), typeid(SpriteComponent).name());
	}
	catch (ErrorHandler e) { sprite = &entity->addCompoent<SpriteComponent>(); }
	catch (std::exception& ex) { cout << ex.what() << endl; }
	
	if (entity->hasComponent<DynamicCollisionComponent>())
		dynamic_col = entity->getComponent<DynamicCollisionComponent>();
}

void KeyboardControllerComponent::handleEvents()
{
	// Facem animatia de zbor a pasarii, daca nu e pe pamant inseamna ca zboara si daca e pe pamant si are animatia de fly o dezactivam
	// Nu prea am stiut unde sa o mai pun si pe asta deci a ajuns aici...
	if (dynamic_col && sprite->isAnimated())
	{
		if (dynamic_col->onGround)
		{
			if (sprite->playingThisAnimation("Fly"))
				sprite->playAnimation("Idle");
			if(GameInfoStorage::PlayerWon)
				if (!sprite->playingThisAnimation("Eat"))
					sprite->playAnimation("Eat", EntityConstructor::AnimationAfter_playerWin);
		}
		else
			if (!sprite->playingThisAnimation("Fly"))
				sprite->playAnimation("Fly");
	}
	if (able_to_move)
	{
		// position->sign semnaleaza pe ce axe entitatea se misca(0 = nu se misca) si in ce directie(-1 = stanga, 1 = dreapta)
		// Tasta apasata

		// Verificam daca tasta W este apasata(pentru a putea apsa mai multe taste simultan)
		if (Game::keys_state[SDL_SCANCODE_W])
		{
			if (dynamic_col && dynamic_col->onGround)
			{
				position->sign.y = -1;
				//up = true;
			}
		}
		if (Game::event.type == SDL_KEYDOWN)
		{
			if (Game::event.key.keysym.sym == SDLK_a)
			{
				// Daca el nu se misca in directia opusa in mom. de fata
				if (!right)
				{
					position->sign.x = -1;
				}
				if (sprite->isAnimated())
				{
					if (!sprite->playingThisAnimation("Fly"))
						sprite->playAnimation("Walk");
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				}
				left = true;
			}
			if (Game::event.key.keysym.sym == SDLK_d)
			{
				// Daca el nu se misca in directia opusa in mom. de fata
				if (!left)
				{
					position->sign.x = 1;
				}
				if (sprite->isAnimated() && !sprite->playingThisAnimation("Fly"))
					sprite->playAnimation("Walk");
				right = true;
			}
			if (DEBUG == 1 && Game::event.key.keysym.sym == SDLK_e)
			{
				EntityConstructor::spawnGoldenEgg(EntityConstructor::golden_egg_spawn_position);
			}

			if (Game::event.key.keysym.sym == SDLK_SPACE)
			{
				//eeeeeggg
				if (!ChickenAttack::eggSpawned())
				{
					if (sprite->spriteFlip == SDL_FLIP_NONE)
						ChickenAttack::setEgg(&EntityConstructor::spawnEgg(Vector2D(position->position.x + ((16 - 10) * position->scale), position->position.y + (48 * position->scale))));
					else
						ChickenAttack::setEgg(&EntityConstructor::spawnEgg(Vector2D(position->position.x + position->width - ((16 - 10) * position->scale), position->position.y + (48 * position->scale))));
				}

			}
		}
		// Tasta eliberata
		else {
			if (Game::event.type == SDL_KEYUP)
			{
				/*if (Game::event.key.keysym.sym == SDLK_w)
				{
					up = false;
				}*/

				if (Game::event.key.keysym.sym == SDLK_a)
				{
					// Bug fix: cand schimbai rapid directia stanga dreapta se bloca pe moement dubios..
					if (right)
					{
						// Bug fix: daca apesi scurt cealata tasta schimba directia de miscare, verificam daca el inca se misca pe directia respectiva deci nu trebuie sa o modificam
						if (!(position->velocity.x > 0))
							position->velocity.x *= -1;
					}
					else
					{
						position->velocity.x = 0;
						if (sprite->isAnimated() && sprite->playingThisAnimation("Walk"))
							sprite->playAnimation("Idle");
					}
					if (sprite->isAnimated())
						sprite->spriteFlip = SDL_FLIP_NONE;
					position->sign.x = 0;
					left = false;
				}
				if (Game::event.key.keysym.sym == SDLK_d)
				{
					// Bug fix: cand schimbai rapid directia stanga dreapta se bloca pe moement dubios..
					if (left)
					{
						// Bug fix: daca apesi scurt cealata tasta schimba directia de miscare, verificam daca el inca se misca pe directia respectiva deci nu trebuie sa o modificam
						if (!(position->velocity.x < 0))
							position->velocity.x *= -1;
					}
					else
					{
						position->velocity.x = 0;
						if (sprite->isAnimated() && sprite->playingThisAnimation("Walk"))
							sprite->playAnimation("Idle");
					}
					position->sign.x = 0;
					right = false;
				}
			}
		}
	}
}