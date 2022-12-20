#include "CameraTarget.h"
#include "PositionComponent.h"
#include "Map.h"


Vector2D CameraTarget::oldCameraPos = Vector2D(0, 0);
Vector2D CameraTarget::camera = Vector2D(0, 0);
Vector2D CameraTarget::cameraOffset = Vector2D(0, 0);
PositionComponent* CameraTarget::targetpos = nullptr;


void CameraTarget::init()
{
	targetpos = entity->getComponent<PositionComponent>();
}

void CameraTarget::Cameraupdate()
{
	camera.x = targetpos->position.x - SCR_W / 2;
	camera.y = targetpos->position.y - SCR_H / 2;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > Map::cols * TILE_SIZE - SCR_W)
		camera.x = Map::cols * TILE_SIZE - SCR_W;
	if (camera.y > Map::rows * TILE_SIZE - SCR_H)
		camera.y = Map::rows * TILE_SIZE - SCR_H;

	cameraOffset.x = camera.x - cameraOffset.x;
	cameraOffset.y = camera.y - cameraOffset.y;
}
