#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H


#include "../ECS/Entity.h"

struct Player : Entity {

  explicit Player(Scene* scene);

  void render(float deltaTime) override;
  void update(float deltaTime) override;

};


#endif
