# Chicken-Quiest
This is my **2D game** made in C++ using SDL2 library

The game is about a **chicken** that needs to **fight some dogs** that toke the **Magic Chocolate Egg** from her Town.

If the chicken **beats all the dogs** it can take then the magic egg and **complete the level**. You need to **collect the stolen eggs** from every level to help the Chicken Town.

Our chicken is not a simple chicken, the special abillity is that it's **eggs explodes**

## How to play
**Beat all the dogs** by egging near them and wait for the **egg to explode**, but the dogs are moving and it is not that easy.

You need to avoid the dogs because if they **hit you, you are death**.

After killing all the enemies you can go and **collect the Magic Egg** that will spawn on the map.

**The controlles** are simple: **W/A/S/D** - _movement_, **Space** - _egg_

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

## Game screenshots

<p align="center" styple="bold">
<img width="800" src="https://user-images.githubusercontent.com/20514478/227737974-770b9fb1-5035-4273-97f2-8b44c88a5d9d.png" alt="Game main menu">
</p>
<p align="center" styple="bold">
<b>Game main menu</b>
</p>

<p align="center" styple="bold">
<img width="800" src="https://user-images.githubusercontent.com/20514478/227737984-9d54ade6-f4d2-4a31-8f7f-f95cdf668895.png" alt="Gameplay screenshot">
</p>
<p align="center" styple="bold">
<p align="center"><b>Gameplay screenshot</b></p>
</p>


