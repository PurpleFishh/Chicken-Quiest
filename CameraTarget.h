#pragma once
#include "ECS.h"
#include "Vector2D.h"
#include "PositionComponent.h"

class CameraTarget : public Component
{
private:
	static Vector2D oldCameraPos;
	static PositionComponent *targetpos;
public:
	static Vector2D camera, cameraOffset;
	void init() override;
	static void Cameraupdate();
};

