#ifndef RPG_SCENE_H
#define RPG_SCENE_H


#include <entt/entt.hpp>

struct Entity;

struct Scene {

  entt::registry registry;
  Entity createEntity();
  Scene() = default;
  Entity* currentCamera;

};


#endif //RPG_SCENE_H
