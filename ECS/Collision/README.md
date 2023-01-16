# Collision
There are all the collision detection and solver classes
**CollisionComponent.cpp**: 
- this is added to every entity that has ***collision***
  - the entities with this compoment will be ***checked when doing collisions***
  - in ***Debug Mode*** the entities will have ***hit-box***
**DynamicCollisionComponent.cpp**:
- this component is used for ***moving entites***
  - the class contains all  collision ***detection and solver function***(tiles collision, player-enemy collision, explosion collision, winning egg collision, map border)
  - it has a main function ***collsionManager*** which gets 2 bools for ***flags modify***, ***a list*** of in which enitites it needs to serach for collision and one ***pointer to an function*** for ***collision detection*** and another for ***collision solver***
  - if you select flags modify it will check if the entity is ***on ground*** and in which ***corrner the entity has collision***
**MouseCollision.cpp**:
- this component is used for ***mouse collision***:
  - used mostly for _buttons_ it check if the entity _(button)_ is ***clicked, hovered***
  - it handels what needs to happen if the button is clicked from the ***specification*** _(an string id)_
