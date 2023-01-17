# Chicken-Quiest
This is my **2D game** made in C++ using SDL2 library

The game is about a **chicken** that needs to **fight some dogs** that toke the **Magic Chocolate Egg** from her Town
The special abillity of that chicken is that her **eggs explodes**

## How to play
The controlles are simple: W/A/S/D - movement, F - egg

## Code documentation
### ECS
- The game is using an **ECS _(Entity Component System)_**
  - Basically this is how the engine works:
      - you add **Entitie** to the game
      - you can add **Components** to that **Entity**
      - when the engine is running the **System** is managing everything: initialization, drawing, update and event handeling for every entity
      ```
      // Here is an code example of how to use the ECS
      auto& player = ECS_Manager.addEntity(); // creating entity
	  player.addCompoent<PositionComponent>(spawn_position.x, spawn_position.y, PLAYER_H, PLAYER_W, 1.0f, 1.f, true); // adding PostionComponent
	  player.addCompoent<SpriteComponent>(Textures::animations_textures.at(0), Textures::animations.at(0)); // adding SpriteComponent
      ```
### Game.cpp
- here is where the System is running and where the game lodes the libraries and the info necessary
### settings.h
- here is a header file where can be found all the info that the game is using (tile size, speed, file path and format, etc.)
### Main.cpp
- here we just start the game engine
