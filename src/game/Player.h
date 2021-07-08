#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "../ECS/Entity.h"

struct Player : Entity {

  explicit Player(Scene* scene);
  void construct();

  float speed = 0.7f;

};

void playerMoveLeft(Player& entity);
void playerMoveRight(Player& entity);
void playerMoveUp(Player& entity);
void playerMoveDown(Player& entity);

// This acts as a ID for when you need to loop through certain types of entities.
struct PlayerEntityID {
  bool placeholder;
};

#endif
