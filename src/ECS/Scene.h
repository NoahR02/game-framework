#ifndef RPG_SCENE_H
#define RPG_SCENE_H


#include <entt/entt.hpp>

struct Entity;

struct Scene {

  entt::registry registry;
  Entity createEntity();

  template<typename T, typename = std::enable_if<std::is_base_of<Entity, T>::value>>
  T createEntitySubClass() {
    return T(this);
  }


  Scene() = default;
  Entity* currentCamera;

};


#endif //RPG_SCENE_H
