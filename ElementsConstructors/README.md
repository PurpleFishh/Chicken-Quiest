# ElementsConstructors
## EntityConstructor.cpp
- here are all the **constructors for entities** like: ***player, enemy, egg, winning egg, explosion, background image, text and info bar***
- the function take as parameter a ***Vector*** which is the ***position***, the ***scen*** and ***layer*** where it will be rendered and ***other specific*** things for the constructor _(text, texture id, etc.)_
## MenuConstructor.cpp
- here are all the **constructor for menu** needed things _(also entities)_ like ***buttons***
- the function parameters are: ***scen id, layer id, Position Vector, button specialization, texture id, button width, button height, original sprite width and height***
## ScenesManager.cpp
- here is the **scenes manager**: it is working with an ***stack*** and always work with the ***top of the stack*** and renders it
- it is handeling the work with the stack: ***pop, get the top, distroy current showing scen***
- every function ***push the scen*** on the stack and checks if the scen ***is loded*** or if it needs to ***add the needed entities*** _(using an array of bools with the index of the scen)_
- scenes: ***startLevel*** _(loades the wanted level)_, ***showMain_Menu*** _(the main menu of the game)_, ***showLevels_Menu*** _(where you select the level)_, ***showPause_Menu*** _(pause menu)_, ***showWin_Screen*** _(screen when you win)_, ***showGameOver_Screen*** _(game over screen)_
