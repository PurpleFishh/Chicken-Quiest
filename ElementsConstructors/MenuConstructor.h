#pragma once
#include "../ECS/ECS.h"
#include "../Utils/Vector2D.h"
#include <map>
#include <string>

class MenuConstructor
{
public:
	static std::map<Entity* ,std::string> menu_entities_specialization;

	static Entity& spawnBackground(const Vector2D& spawn_position);
	static Entity& spawnLogo(const Vector2D& spawn_position);
	static Entity& spawnButton(int scen, int layer, const Vector2D& spawn_position, std::string specialization, int texture_id, int w, int h, int scrw, int scrh);
};

