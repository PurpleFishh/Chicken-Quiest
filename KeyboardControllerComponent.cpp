#include "KeyboardControllerComponent.h"
#include "DynamicCollisionComponent.h"
#include "Game.h"

void KeyboardControllerComponent::init()
{
	position = entity->getComponent<PositionComponent>();
}

void KeyboardControllerComponent::handleEvents()
{
	// position->sign semnaleaza pe ce axe entitatea se misca(0 = nu se misca) si in ce directie(-1 = stanga, 1 = dreapta)
	// Tasta apasata

	// Verificam daca tasta W este apasata(pentru a putea apsa mai multe taste simultan)
	if (Game::keys_state[SDL_SCANCODE_W])
	{
		bool& onGround = entity->getComponent<DynamicCollisionComponent>()->onGround;
		if (onGround)
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
			left = true;
		}
		if (Game::event.key.keysym.sym == SDLK_d)
		{
			// Daca el nu se misca in directia opusa in mom. de fata
			if (!left)
			{
				position->sign.x = 1;
			}
			right = true;
		}
		if (Game::event.key.keysym.sym == SDLK_r) 
		{
			entity->destroy();
			cout << "Entity destroyed" << endl;
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
					position->velocity.x = 0;

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
					position->velocity.x = 0;

				position->sign.x = 0;
				right = false;
			}
		}
	}
}