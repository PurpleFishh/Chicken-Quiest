#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "DynamicCollisionComponent.h"
#include "settings.h"

PositionComponent::PositionComponent()
{
	position.x = position.y = 0;
}
PositionComponent::PositionComponent(float scale)
{
	position.x = position.y = 0;
	this->scale = scale;
}
PositionComponent::PositionComponent(float x, float y)
{
	position.x = x;
	position.y = y;
}
PositionComponent::PositionComponent(float x, float y, float scale)
{
	position.x = x;
	position.y = y;
	this->scale = scale;
}
PositionComponent::PositionComponent(float x, float y, int h, int w, float speed, float scale)
{
	position.x = x;
	position.y = y;
	height = h;
	width = w;
	this->speed = speed;
	this->scale = scale;
}
PositionComponent::PositionComponent(float x, float y, int h, int w, float speed, float scale, bool gravity)
{
	position.x = x;
	position.y = y;
	height = h;
	width = w;
	this->speed = speed;
	this->scale = scale;
	this->gravity = gravity;
}

void PositionComponent::init()
{
	velocity.x = 0;
	velocity.y = 0;
}
void PositionComponent::update()
{
	float new_velocity_x = velocity.x + (delta_time / 1000) * sign.x;
	float new_velocity_y = velocity.y + (delta_time / 1000) * sign.y;
	
	// Miscare pe axa X
	if (sign.x && abs(new_velocity_x) < max_speed)
	{
		velocity.x = new_velocity_x;
	}

	// Daca entitatea are gravitatie
	if (gravity)
	{

		// Daca ajunge la inaltimea maxima a sariturii aplicam inapoi gravitatiea
		if (sign.y == -1 && abs(new_velocity_y) >= max_jump)
			sign.y = 1;
		// Daca e nevoie de gravidatie, nu o lasam sa treaca de maximul acesteia
		if (sign.y == 1 && new_velocity_y >= gravity_speed)
			new_velocity_y = velocity.y;

		velocity.y = new_velocity_y;
	}
	else
		// Miscare pe axa Y(ca o fantoma ;))
		if (sign.y && abs(new_velocity_y) < max_speed)
		{
			velocity.y = new_velocity_y;
		}


	position.x += velocity.x * delta_time * speed;
	position.y += velocity.y * delta_time * speed;
}