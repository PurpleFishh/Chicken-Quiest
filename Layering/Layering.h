#pragma once

#include "settings.h"
#include "ECS.h"

#include <array>
#include <vector>
#include <map>
#include <stack>

using namespace std;

/**
 * @brief Class for managing layers and scenes
*/
class Layers
{
private:

public:
	/**
	 * @brief Scenes enum
	*/
	enum scenes
	{
		scenMainMenu,		///< Main menu scen
		scenLevelsMenu,		///< Levels selection menu scen
		scenPauseMenu,		///< Pause menu scen
		scenGame,			///< Gameplay scen
		scenGameOver,		///< Game over scen
		scenGameWin			///< Win screen scen
	};

	/// Game level layers rendering order
	enum class game_layers
	{
		layerCollision,		///< Collision layer
		layerBackground,	///< Background layer
		layerMap,			///< Map layer with the tiles
		layerGoldenEggs,	///< Golden eggs layer
		layerPlayer,		///< Player layer
		layerEnemy,			///< Enemy layer
		layerEggs,			///< Eggs layer
		layerExplosion,		///< Explosion layer
		layerBar			///< Infobar layer
	};
	/// Main menu layers rendering order
	enum class main_menu_layers
	{
		layerBackground,	///< Background layer
		layerButtons,		///< Buttons layer
		layerLogo			///< Logo layer
	};
	/// Levels selection menu layers rendering order
	enum class levels_menu_layers
	{
<<<<<<< Updated upstream:Layering.h
		layerBackground,
		layerButtons
=======
		layerBackground,	///< Background layer
		layerButtons,		///< Buttons layer
		layerBar			///< Infobar layer
>>>>>>> Stashed changes:Layering/Layering.h
	};
	/// Pause menu layers rendering order
	enum class pause_menu_layers
	{
		layerBackground,	///< Background layer
		layerButtons,		///< Buttons layer
		layerBanner			///< Banner layer
	};
	/// Win screen layers rendering order
	enum class win_screen_layers
	{
		layerBackground,	///< Background layer
		layerButtons,		///< Buttons layer
		layerBanner			///< Banner layer
	};
	/// Game over layers rendering order
	enum class gameover_screen_layers
	{
		layerBackground,	///< Background layer
		layerButtons,		///< Buttons layer
		layerBanner			///< Banner layer
	};
	//static array<vector<Entity*>, LAYERS_NUM> layers;
	/**
	* @brief A map of ints (scen id) and a array (the index represents the layer id) of an vector of Entities (the entites that are in that layer)
	*/
	static map<int, array<vector<Entity*>, LAYERS_NUM>> layers;
	/**
	 * @brief A stack of ints (scen id)
	 * @details The top of the stack is the shown scen
	*/
	static stack<int> ScenesStack;

	/**
	* @brief Add an entity to the specified scen and layer
	* @param scen The scen id
	* @param entity The entity to add
	* @param id The layer id
	*/
	static void add(int scen, Entity* entity, int id);

	/**
	* @brief Remove that entity form the scen
	* @param scen The scen id
	* @param entity The entity to remove
	*/
	static void removeEntity(int scen, Entity* entity);
	/**
	* @brief Destroy every entity form the layer and clears it
	* @param scen The scen id
	* @param layer The layer id
	*/
	static void clearLayer(int scen, int layer);
	/**
	* @brief Clear the layer that was given as parameter
	* @param layer The layer to clear
	*/
	static void clearLayer(std::vector<Entity*>& layer);
	/**
	* @brief Destroy every entity form the scen and clears it(and all the layers)
	* @param scen The scen id
	*/
	static void clearScen(int scen);

	/**
	* @brief Render all the entities form the layers of the scen
	*/
	static void renderLayers(int scen);
	/**
	* @brief Hnadlers the events for all the entities form the layers of the scen
	*/
	static void handlerLayers(int scen);
	/**
	* @brief Update all the entities form the layers of the scen
	*/
	static void updateLayers(int scen);

	/**
	* @brief Get the entity from the layer
	* @param scen The scen id
	* @param layer The layer id
	* @param id The entity id
	* @return return the entity
	*/
	static Entity* getEntityfromLayer(int scen, int layer, int id);
	/**
	* @brief Get the layer
	* @param scen The scen id
	* @param layer The layer id
	* @return return the layer vector
	*/
	static vector<Entity*>& getLayer(int scen, int layer);
	/**
	* @brief Get the scen
	* @param scen The scen id
	* @return return the array of the layers of the scen
	*/
	static array<vector<Entity*>, LAYERS_NUM>& getScen(int scen);
};
