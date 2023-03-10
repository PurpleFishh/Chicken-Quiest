#pragma once
#include "../ECS.h"
#include "../../Utils/Vector2D.h"
#include "../Movement/PositionComponent.h"

class CameraTarget : public Component
{
private:
	static Vector2D oldCameraPos;
	static PositionComponent *targetpos;
public:
	static bool hasTarget;
	static Vector2D camera, cameraOffset;
	void init() override;
	static void Cameraupdate();
};

