#pragma once
#include "../ECS.h"
#include "../../Utils/Vector2D.h"

class PositionComponent : public Component
{
public:
	Vector2D position, velocity;
	// sign semnaleaza pe ce axe entitatea se misca(0 = nu se misca) si in ce directie(-1 = stanga, 1 = dreapta)
	Vector2D sign = Vector2D(0, 0);
	float speed = 1, scale = 1;
	int height = TILE_SIZE, width = TILE_SIZE;
	bool gravity = false;

	PositionComponent();
	PositionComponent(float scale);
	PositionComponent(float x, float y);
	PositionComponent(float x, float y, float scale);
	PositionComponent(float x, float y, int h, int w);
	PositionComponent(float x, float y, int h, int w, float speed, float scale);
	PositionComponent(float x, float y, int h, int w, float speed, float scale, bool gravity);

	void init() override;
	void update() override;

	Vector2D getPotentialPosition();
	Vector2D getPotentialVelocity();
};