#ifndef RPG_ENTITY_H
#define RPG_ENTITY_H


#include "Scene.h"
#include "Body.h"
#include "Sprite.h"
#include <entt/entt.hpp>
#include <iostream>

struct Entity {

  entt::entity id;
  Scene* scene;

  Entity(Scene* scene): id(scene->registry.create()), scene(scene) {
    onCreate();
  }

  Entity(Scene* scene, entt::entity): id(id), scene(scene) {
    onCreate();
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

  Body& addBody() {
    Body& body = scene->registry.emplace<Body>(id);
    scene->world.createBody(body);

    return body;
  };

  template<typename T>
  T& getComponent() {
    return scene->registry.get<T>(id);
  }

  virtual void onCreate() {
  }

  virtual void update(float deltaTime) {

  }

  virtual void render(float deltaTime) {
  }

};

#endif
