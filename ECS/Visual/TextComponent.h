#pragma once
#include "SpriteComponent.h"
#include "../../Game.h"
#include <SDL_ttf.h>

/**
* @class TextComponent
* @brief Class that will render text on the screen
*/
class TextComponent : public SpriteComponent
{
private:
	/// <summary>
	/// The text that will be rendered
	/// </summary>
	std::string text;
	/// <summary>
	/// The color of the text
	/// </summary>
	SDL_Color color;
public:
	/**
	* @brief Construct a new Text Component object
	* @param text The text that will be rendered
	* @param color The color of the text
	*/
    TextComponent(const std::string& text, const SDL_Color& color);

	void init() override;
	
	/**
	 * @brief Set the Text object
	 * @param text The text that will be rendered
	 * @param color The color of the text
	*/
	void setText(const std::string& text, const SDL_Color& color);
};
