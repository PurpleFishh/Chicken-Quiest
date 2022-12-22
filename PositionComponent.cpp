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

	
	/*{
		cout << position << endl;
		cout << velocity << endl;
		cout << sign << endl;
		cout << height << width << endl;
	}*/
}
void PositionComponent::update()
{
	if (entity->getLayer_Id() == 2)
		cout << position << endl;
	setNewPosition();
}

void PositionComponent::setNewPosition()
{
	velocity = getPotentialVelocity();
	position = getPotentialPosition();
}

Vector2D PositionComponent::getPotentialVelocity()
{
	Vector2D potVelocity = velocity;
	float new_velocity_x = potVelocity.x + (delta_time / 1000) * sign.x;
	float new_velocity_y = potVelocity.y + (delta_time / 1000) * sign.y;

	// Miscare pe axa X
	if (sign.x && abs(new_velocity_x) < max_speed)
	{
		potVelocity.x = new_velocity_x;
	}

	// Daca entitatea are gravitatie
	if (gravity)
	{

		// Daca ajunge la inaltimea maxima a sariturii aplicam inapoi gravitatiea
		if (sign.y == -1 && abs(new_velocity_y) >= max_jump)
			sign.y = 1;
		// Daca e nevoie de gravidatie, nu o lasam sa treaca de maximul acesteia
		if (sign.y == 1 && new_velocity_y >= gravity_speed)
			new_velocity_y = potVelocity.y;

		potVelocity.y = new_velocity_y;
	}
	else
		// Miscare pe axa Y(ca o fantoma ;))
		if (sign.y && abs(new_velocity_y) < max_speed)
		{
			potVelocity.y = new_velocity_y;
		}

	return potVelocity;
}
Vector2D PositionComponent::getPotentialPosition()
{
	Vector2D potPosition = position;
	potPosition.x += velocity.x * delta_time * speed;
	potPosition.y += velocity.y * delta_time * speed;
	return potPosition;
}