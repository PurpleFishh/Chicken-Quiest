# Chicken-Quiest
This is my 2D game made in C++ using SDL2 library

The game is about a chicken that needs to fight some dogs that toke the Magic Chocolate Egg from her Town
The special abillity of that chicken is that her eggs explodes

## How to play
The controlles are simple: W/A/S/D - movement, F - egg

## Code documentation
- The game is using an **ECS _(Entity Component System)_**
  - Basically this is how the engine works:
      - you add **Entitie** to the game
      - you can add **Components** to that **Entity**
      - when the engine is running the **System** is managing everything: initialization, drawing, update and event handeling for every entity
- In Game.cpp is where the System is running and where the game lodes the libraries and the info necessary
- settings.h is a header file where can be found all the info that the game is using (tile size, speed, file path and format, etc.)
- In Main.cpp we just start the game engine
