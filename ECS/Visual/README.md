# Visual
## SpriteComponent.cpp
- this component is dealing with the **sprite rendering** at the needed position
  - it uses the ***CameraTarget.cpp*** to calculate where it needs to render the sprites for ***camera movement***
## TextComonent.cpp
- this component is a ***child of SpriteComponent.cpp*** and with it you can **render text on screen**
  - you can specify the _position, text and color_
## Infobar.cpp
- this class is used to **display informations** about the game like ***life, time until you can attack again, score, best score, enemies alive***
  - it is using _a code_ to know what to display in the ***Info Bar***
