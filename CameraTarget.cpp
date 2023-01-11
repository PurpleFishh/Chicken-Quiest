#include "CameraTarget.h"
#include "PositionComponent.h"
#include "Map.h"
#include "ErrorHandler.h"


Vector2D CameraTarget::oldCameraPos = Vector2D(0, 0);
Vector2D CameraTarget::camera = Vector2D(0, 0);
Vector2D CameraTarget::cameraOffset = Vector2D(0, 0);
PositionComponent* CameraTarget::targetpos = nullptr;
bool CameraTarget::hasTarget = false;


void CameraTarget::init()
{
	hasTarget = true;
	try {
		targetpos = entity->getComponent<PositionComponent>();
		if (!entity->hasComponent<PositionComponent>())		throw ErrorHandler(typeid(CameraTarget).name(), typeid(PositionComponent).name());
	}
	catch (ErrorHandler e) { targetpos = &entity->addCompoent<PositionComponent>(); }
	catch (std::exception& ex) { cout << ex.what() << endl; }
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
		camera.x = (float)Map::cols * TILE_SIZE - SCR_W;
	if (camera.y > Map::rows * TILE_SIZE - SCR_H)
		camera.y = (float)Map::rows * TILE_SIZE - SCR_H;

	cameraOffset.x = camera.x - cameraOffset.x;
	cameraOffset.y = camera.y - cameraOffset.y;
}
