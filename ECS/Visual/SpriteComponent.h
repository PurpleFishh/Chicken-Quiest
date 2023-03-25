#pragma once
#include "SDL_image.h"
#include "../ECS.h"
#include "../Movement/PositionComponent.h"
#include "../../Utils/TexturesTools/TextureManager.h"
#include "../../Utils/TexturesTools/Textures.h"
#include "../../ElementsConstructors/EntityConstructor.h"
#include "../../Utils/Vector2D.h"
#include "../../settings.h"

/**
* @brief Component for rendering sprites and playing animations
*/
class SpriteComponent : public Component
{
protected:
	/// <summary>
	/// The SDL texture used for the entity
	/// </summary>
	SDL_Texture* texture;
	/// <summary>
	///  If the entity is animated
	/// </summary>
	bool animated = false;
	/// <summary>
	/// A pointer to a function that will be called after the animation is played once and if nullptr, the animation will be played in a loop
	/// </summary>
	void(*PlayOnceAfterPlay)(Entity* entity) = nullptr;
	/// <summary>
	/// The animations of the entity
	/// </summary>
	animations_type animations;
	/// <summary>
	/// The animation row that is currently playing (the row in the texture), the number of frames in the animation, the speed of the animation, the animation timer
	/// </summary>
	int animation_row = 0, frames = 0, speed = 100, animation_timer = 0;
	/// <summary>
	/// The width and height of the source image, the texture id(-1 if not settd, the is the index of the texture in the texture loaded vectors)
	/// </summary>
	int src_width = 0, src_height = 0, texture_id = -1;

	/// <summary>
	/// A pointer to the position component of the entity
	/// </summary>
	PositionComponent* posdetails;
public:
	/// <summary>
	/// The source and destination rectangles of the entity
	/// </summary>
	SDL_Rect srcRect;
	SDL_Rect destRect;
	/// <summary>
	/// The flip of the sprite
	///	</summary>
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	/**
	* @brief Construct a new Sprite Component object
	*/
	SpriteComponent() = default;
	/**
	* @brief Construct a new Sprite Component object
	* @param textureFile The path to the texture used
	*/
	SpriteComponent(const char* textureFile);
	/**
	* @brief Construct a new Sprite Component object
	* @param texture The texture used for the entity, thexture form the vectors of loaded textures
	*/
	SpriteComponent(SDL_Texture* texture);
	/**
	* @brief Construct a new Sprite Component object
	* @param texture The texture used for the entity, texture form the vectors of loaded textures
	* @param texture_id The id of the texture in the vectors of loaded textures
	*/
	SpriteComponent(SDL_Texture* texture, int texture_id);
	/**
	* @brief Construct a new Sprite Component object
	* @param texture The texture used for the entity, texture form the vectors of loaded textures
	* @param src_width The width of the source image
	* @param src_height The height of the source image
	*/
	SpriteComponent(SDL_Texture* texture, int src_width, int src_height);
	/**
	* @brief Construct a new Sprite Component object
	* @param texture The texture used for the entity, texture form the vectors of loaded textures
	* @param src_width The width of the source image
	* @param src_height The height of the source image
	* @param texture_id The id of the texture in the vectors of loaded textures
	*/
	SpriteComponent(SDL_Texture* texture, int src_width, int src_height, int texture_id);
	/**
	* @brief Construct a new Sprite Component object
	* @param texture The texture used for the entity, texture form the vectors of loaded textures
	* @param animations The animations of the entity
	*/
	SpriteComponent(SDL_Texture* texture, animations_type animations);
	/**
	* @brief Construct a new Sprite Component object
	* @param texture The texture used for the entity, texture form the vectors of loaded textures
	* @param animations The animations of the entity
	* @param src_width The width of the source image
	* @param src_height The height of the source image
	*/
	SpriteComponent(SDL_Texture* texture, animations_type animations, int src_width, int src_height);
	/**
	* @brief Construct a new Sprite Component object
	* @param texture The texture used for the entity, texture form the vectors of loaded textures
	* @param animations The animations of the entity
	* @param PlayOnceAfterPlay A pointer to a function that will be called after the animation is played once and if nullptr, the animation will be played in a loop
	*/
	SpriteComponent(SDL_Texture* texture, animations_type animations, void(*PlayOnceAfterPlay)(Entity* entity));

	/**
	* @brief Set a new texture to the Sprite Component
	* @param textureFile The path to the texture used
	*/
	void setTexture(const char* textureFile);
	/**
	* @brief Set a new texture to the Sprite Component
	* @param texture The texture used for the entity, texture form the vectors of loaded textures
	*/
	void setTexture(SDL_Texture* texture);
	/**
	 * @brief Set a new texture to the Sprite Component
	 * @param texture The texture used for the entity, texture form the vectors of loaded textures
	 * @param texture_id The id of the texture in the vectors of loaded textures
	 */
	void setTexture(SDL_Texture* texture, int texture_id);
	/**
	* @brief Set a new texture to the Sprite Component
	* @param texture The texture used for the entity, texture form the vectors of loaded textures
	* @param animations The animations of the entity
	*/
	void setTexture(SDL_Texture* texture, animations_type animations);

	/**
	* @brief The function that is called when entity is initialized
	*/
	void init() override;
	/**
	* @brief The function that is called when entity is updated
	*/
	void update() override;
	/**
	* @brief The function that is called when entity is drawn
	*/
	void draw() override;

	/**
	* @brief Play an animation
	* @param animationName The name(given nickname) of the animation
	*/
	void playAnimation(std::string animationName);
	/**
	* @brief Play an animation
	* @param animationName The name(given nickname) of the animation
	* @param PlayOnceAfterPlay A pointer to a function that will be called after the animation is played once and if nullptr, the animation will be played in a loop
	*/
	void playAnimation(std::string animationName, void(*PlayOnceAfterPlay)(Entity* entity));
	/**
	* @brief Get if an specific animation is seted to the entity
	* @param animationName The name(given nickname) of the animation
	* @return true if the animation is playing
	*/
	bool playingThisAnimation(std::string animationName);
	/**
	* @brief Get if the entity is animated
	* @return true if the entity is animated
	*/
	bool isAnimated() { return animated; }
	/**
	* @brief Get the texture id
	* @return The texture id
	*/
	int getTexture_id() { return texture_id; }
};
