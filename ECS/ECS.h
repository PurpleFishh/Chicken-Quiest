#pragma once

#include "../settings.h"

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

using namespace std;

class Component;
class Entity;

/// Obtain the next valid id
inline size_t getComponentId()
{
	static size_t lastComponentId = 0;
	return lastComponentId++;
}

/// <summary>
/// Obtain the id of the component
/// </summary>
/// <typeparam name="T">The component to find it's id</typeparam>
/// <returns></returns>
template <typename T>
inline size_t getComponentId()
{
	// Verificam daca clasa T este un Compoent(derivata din Clasa Component)
	static_assert (std::is_base_of<Component, T>::value, "ERROR: Clasa nu este fiica a Clasei Component");
	static size_t lastComponentId = getComponentId();
	return lastComponentId;
}

/**
* @brief Compoent is an absstract class that is used to create components for entities
*/
class Component
{
public:
	/// The entity that owns the component
	Entity* entity = nullptr;

	/**
	* @brief This function is used to initialize the component
	*/
	virtual void init() {}
	/**
	 * @brief This function is used to update the component
	*/
	virtual void update() {}
	/**
	 * @brief This function is used to handle the events of the component
	*/
	virtual void handleEvents() {}
	/**
	 * @brief This function is used to render the component
	*/
	virtual void draw() {}
	/**
	 * @brief This function is used to destroy the component
	*/
	virtual ~Component() {}
};

/**
 * @brief Used to create entities and add components to them
*/
class Entity
{
private:
	/// <summary>
	/// If the entity is active or not
	/// </summary>
	bool active = true;
	
	/// <summary>
	/// A vector of the components that are associated with the entity
	/// </summary>
	vector<unique_ptr<Component>> components;

	/// <summary>
	/// Check the components that te entity owns
	/// </summary>
	bitset<maxComponents> componentBitset;
	
	/// <summary>
	/// An array of the components that are associated with the entity using the index as the id of the component
	/// </summary>
	array<Component*, maxComponents> componentArray;
	
	/// <summary>
	/// The id of the layer that the entity is in(-1 if the entity is not in a layer)
	/// </summary>
	int Layer_Id = -1;
public:
	/**
	 * @brief This function is called when the entity is destroyed
	*/
	~Entity()
	{
		active = false;
		cout << "Entity destroyed" << endl;
	}
	
	/**
	 * @brief Call the update function for all the components that the entity has
	*/
	void update()
	{
		for (auto& component : components)
		{
			component->update();
		}
	}
	/**
	 * @brief Call the draw function for all the components that the entity has
	*/
	void draw()
	{
		for (auto& component : components)
			component->draw();
	}
	/**
	 * @brief Call the handleEvents function for all the components that the entity has
	*/
	void handleEvents()
	{
		for (auto& component : components)
			component->handleEvents();
	}
	/**
	 * @brief Get is the entity is active
	 * @return return true if the entity is active and false if it is not
	*/
	bool isActive()
	{
		return active;
	}
	/**
	 * @brief Set the entity to inactive and the entity wil be destroyed in the System::inactive_verify function
	*/
	void destroy()
	{
		active = false;
	}
	
	/**
	 * @brief Get if the entity has a component
	 * @return return true if the entity has the component and false if it does not
	*/
	template<typename T>
	bool hasComponent()
	{
		return componentBitset[getComponentId<T>()];
	}
	
	/**
	 * @brief Add a component to the entity
	 * @return return a referince to the component that was added
	*/
	template<typename T, typename... TArgs>
	T& addCompoent(TArgs&& ... args)
	{
		T* c(new T(forward<TArgs>(args)...));
		c->entity = this;
		unique_ptr<Component> pointer{ c };
		components.emplace_back(move(pointer));

		componentArray[getComponentId<T>()] = c;
		componentBitset[getComponentId<T>()] = true;

		c->init();
		return *c;
	}

	/**
	 * @brief Get a component from the entity
	 * @return return a pointer to the component
	*/
	template<typename T>
	T* getComponent()
	{
		auto component = componentArray[getComponentId<T>()];

		return static_cast<T*>(component);
	}
	
	/**
	* @brief Set the layer id of the entity
	* @param id The id of the layer
	*/
	void setLayer_Id(int id)
	{
		Layer_Id = id;
	}
	/**
	* @brief Get the layer id of the entity
	* @return return the id of the layer
	*/
	inline int getLayer_Id()
	{
		return Layer_Id;
	}
};

/**
* @brief Used to store and manager all the entities
*/
class System
{
private:
	/// <summary>
	/// A vector of all the entities
	/// </summary>
	vector<unique_ptr<Entity>> entities;

public:
	/**
	* @brief Update all the entities by calling the update function for each entity
	*/
	void update()
	{
		for (auto& entity : entities)
		{
			entity->update();
		}
	}
	/**
	* @brief Draw all the entities by calling the draw function for each entity
	*/
	void draw()
	{
		for (auto& entity : entities)
		{
			entity->draw();
		}
	}
	/**
	* @brief Handle all the events of all the entities by calling the handleEvents function for each entity
	*/
	void handleEvents()
	{
		for (auto& entity : entities)
		{
			entity->handleEvents();
		}
	}
	/**
	* @brief Destroy all the entities that are inactive and remove them from the layers that they are in
	*/
	void inactive_verify();
	
	/**
	* @brief Add an entity to the system
	* @return return a referince to the entity that was added
	*/
	Entity& addEntity()
	{
		Entity* e = new Entity();
		unique_ptr<Entity> pointer{ e };
		entities.emplace_back(move(pointer));
		return *e;
	}

};