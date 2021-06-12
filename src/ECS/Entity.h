#ifndef RPG_ENTITY_H
#define RPG_ENTITY_H


#include "Scene.h"
#include <entt/entt.hpp>

struct Entity {

  entt::entity id;
  Scene* scene;

  Entity(Scene* scene): id(scene->registry.create()), scene(scene) {
  }

  template<typename T>
  bool hasComponent() {
    if (scene)
      return scene->registry.any_of<T>(id);
    return false;
  }

  template<typename T, typename... Args>
  T& addComponent(Args&&... args) {
    return scene->registry.emplace<T>(id, std::forward<Args>(args)...);
  }

  template<typename T>
  T& getComponent() {
    return scene->registry.get<T>(id);
  }

};

#endif
