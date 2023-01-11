#pragma once

#include "settings.h"

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

using namespace std;

class Component;
class Entity;

// Obtinem urmatorul id valid
inline size_t getComponentId()
{
	static size_t lastComponentId = 0;
	return lastComponentId++;
}

template <typename T>
inline size_t getComponentId()
{
	// Verificam daca clasa T este un Compoent(derivata din Clasa Component)
	static_assert (std::is_base_of<Component, T>::value, "ERROR: Clasa nu este fiica a Clasei Component");
	static size_t lastComponentId = getComponentId();
	return lastComponentId;
}

class Component
{
public:
	// Entitatea careia ii este asociata componenta
	Entity* entity = nullptr;

	// Functiile componentei pe care le voim suprascrie in functie de caz
	virtual void init() {}
	virtual void update() {}
	virtual void handleEvents() {}
	virtual void draw() {}
	virtual ~Component() {}
};


class Entity
{
private:
	// Daca entitatea este activa
	bool active = true;
	
	vector<unique_ptr<Component>> components;

	// Bifam ce componente sunt asociate entitatii
	bitset<maxComponents> componentBitset;
	// Stocarea componentelor in functie de id-ul obtinut la inregistrare
	array<Component*, maxComponents> componentArray;
	
	// -1 -> nu face parte din niciun Layer
	int Layer_Id = -1;
public:
	~Entity()
	{
		active = false;
		cout << "Entity destroyed" << endl;
	}
	
	// Executam functia de update pentru toate componentele
	void update()
	{
		for (auto& component : components)
		{
			component->update();
		}
	}
	// Executam functia de draw pentru toate componentele
	void draw()
	{
		for (auto& component : components)
			component->draw();
	}
	void handleEvents()
	{
		for (auto& component : components)
			component->handleEvents();
	}
	bool isActive()
	{
		return active;
	}
	// Setam active pe false urmand ca entitatea sa fie dinstrusa in functia System::inactive_verify
	void destroy()
	{
		active = false;
	}
	
	// Verificam daca componenta respectiva este asociata entitatii
	template<typename T>
	bool hasComponent()
	{
		return componentBitset[getComponentId<T>()];
	}
	
	// Adaugam componente entitatii
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

	// Obtinem componenta dorita
	template<typename T>
	T* getComponent()
	{
		auto component = componentArray[getComponentId<T>()];

		return static_cast<T*>(component);
	}

	void setLayer_Id(int id)
	{
		Layer_Id = id;
	}
	inline int getLayer_Id()
	{
		return Layer_Id;
	}
};

class System
{
private:
	vector<unique_ptr<Entity>> entities;

public:
	// Executam functia de update pentru toate entitatile
	void update()
	{
		for (auto& entity : entities)
		{
			entity->update();
		}
	}
	// Executam functia de draw pentru toate entitatile
	void draw()
	{
		for (auto& entity : entities)
		{
			entity->draw();
		}
	}
	void handleEvents()
	{
		for (auto& entity : entities)
		{
			entity->handleEvents();
		}
	}
	// Stergem entitatile inactive
	void inactive_verify();
	
	// Creare entitate
	Entity& addEntity()
	{
		Entity* e = new Entity();
		unique_ptr<Entity> pointer{ e };
		entities.emplace_back(move(pointer));
		return *e;
	}

};