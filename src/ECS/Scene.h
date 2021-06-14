#ifndef RPG_SCENE_H
#define RPG_SCENE_H


#include <entt/entt.hpp>

struct Entity;

struct Scene {

  entt::registry registry;
  Entity createEntity();
  std::vector<Entity*> entities;

  template<typename T, typename = std::enable_if<std::is_base_of<Entity, T>::value>>
  T createEntitySubClass() {
    entities.push_back(new T(this));
    return *reinterpret_cast<T*>(entities.back());
  }

  Entity* getEntityPtr(Entity& entity);

  Scene() = default;
  Entity* currentCamera;

};


#endif //RPG_SCENE_H
