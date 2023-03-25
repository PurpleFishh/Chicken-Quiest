#pragma once

#include "SDL.h"
#include <SDL_ttf.h>
#include "ECS/ECS.h"
#include "Utils/Vector2D.h"

/**
* \brief The game engine class
*/
class Game
{
private:
	/// <summary>
	/// The game is running or not
	/// </summary>
	static bool isRunning;
	/// <summary>
	/// The window of the game
	/// </summary>
	SDL_Window* window;
	
public:
	/**
	*	\brief The constructor of the game
	*/
	Game();
	/**
	*	\brief The destructor of the game
	*	\ details Destroy the game and close the window, libreris and clear the textures
	*/
	~Game();
	
	/**
	*	\brief The renderer of the game
	*/
	static SDL_Renderer* renderer;
	/**
		*	\brief The event handler of the game
	*/
	static SDL_Event event;
	/**
		*	\brief The keys state of the keyboard in the game
	*/
	static const Uint8* keys_state;
	/**
		*	\brief The mouse position in the game
	*/
	static Vector2D mouse_pos;
	/**
		*	\brief The font used in the game
	*/
	static TTF_Font* gameFont;

	/**
		* \brief Initialize the game
	 * \param title The title of the window
	 * \param xpos The x position of the window
	 * \param ypos The y position of the window
	 * \param width The width of the window
	 * \param height The height of the window
	 * \param fullscreen If the window is fullscreen or not
	*/
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	/**
		* \brief Handle the events
		* \details Handle the events of the active scen showing 
	*/
	void handleEvents();
	/**
		* \brief Update the game
		* \details Update the game of the active scen showing
	*/
	void update();
	/**
		* \brief Render the game
		* \details Render the game of the active scen showing
	*/
	void render();

	/**
		* \brief Check if the game is running
		* \return If the game is running or not
	*/
	inline bool getRunning() { return isRunning; }
	/**
		* \brief Stop the game
	*/
	static void stopGame() { isRunning = false; }
};
