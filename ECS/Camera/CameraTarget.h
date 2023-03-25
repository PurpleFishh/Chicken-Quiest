#pragma once
#include "../ECS.h"
#include "../../Utils/Vector2D.h"
#include "../Movement/PositionComponent.h"

/**
* @brief Component for the entity that will be followed by the camera(abstract class)
*/
class CameraTarget : public Component
{
private:
	/// <summary>
	/// Store the old position of the camera for calculating the camera offset
	/// </summary>
	static Vector2D oldCameraPos;
	/// <summary>
	/// Pointer to the PositionComponent of the targeted entity
	/// </summary>
	static PositionComponent *targetpos;
public:
	/// <summary>
	/// Flag for checking if the camera has a target
	/// </summary>
	static bool hasTarget;
	/// <summary>
	/// Camera position and camera offset
	/// </summary>
	static Vector2D camera, cameraOffset;
	void init() override;
	/**
	* @brief Calculate the camera position and updates it
	*/
	static void Cameraupdate();
};

