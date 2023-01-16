# Movement
**PositionComponent.cpp**
- this component deals with the entity ***position***
  - if the entity ***is moving*** you need to use the ***sign Vector*** where you set the ***direction of the movement***
  - if the ***sign is not null*** it will _increase_ in time the ***velocity*** _(speed)_ of the entity until it hits the ***speed limit*** from ***settings.h***
**KeyboardCobtrollerComponent**
- this component is used for entities with ***keyboard controll***
  - it handles the ***key events for movement*** and ***for attack***
  - it also play the needed ***animation*** for the entity activity
**AiBehavior.cpp**
- is used for ***enemies to move*** form on side of the platform to the other
