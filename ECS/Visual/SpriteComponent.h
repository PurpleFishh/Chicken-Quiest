#pragma once
#include "SDL_image.h"
#include "../ECS.h"
#include "../Movement/PositionComponent.h"
#include "../../Utils/TexturesTools/TextureManager.h"
#include "../../Utils/TexturesTools/Textures.h"
#include "../../ElementsConstructors/EntityConstructor.h"
#include "../../Utils/Vector2D.h"
#include "../../settings.h"

class SpriteComponent : public Component
{
protected:
	SDL_Texture* texture;
	bool animated = false;
	void(*PlayOnceAfterPlay)(Entity* entity) = nullptr;
	animations_type animations;
	int animation_row = 0, frames = 0, speed = 100, animation_timer = 0;
	int src_width = 0, src_height = 0, texture_id = -1;

	PositionComponent* posdetails;
public:
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char* textureFile);
	SpriteComponent(SDL_Texture* texture);
	SpriteComponent(SDL_Texture* texture, int texture_id);
	SpriteComponent(SDL_Texture* texture, int src_width, int src_height);
	SpriteComponent(SDL_Texture* texture, int src_width, int src_height, int texture_id);
	SpriteComponent(SDL_Texture* texture, animations_type animations);
	SpriteComponent(SDL_Texture* texture, animations_type animations, int src_width, int src_height);
	SpriteComponent(SDL_Texture* texture, animations_type animations, void(*PlayOnceAfterPlay)(Entity* entity));

	void setTexture(const char* textureFile);
	void setTexture(SDL_Texture* texture);
	void setTexture(SDL_Texture* texture, int texture_id);
	void setTexture(SDL_Texture* texture, animations_type animations);

	void init() override;
	void update() override;
	void draw() override;

	void playAnimation(std::string animationName);
	void playAnimation(std::string animationName, void(*PlayOnceAfterPlay)(Entity* entity));
	bool playingThisAnimation(std::string animationName);
	bool isAnimated() { return animated; }
	int getTexture_id() { return texture_id; }
};
