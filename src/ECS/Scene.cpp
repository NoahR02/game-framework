#include "Scene.h"

#include "Entity.h"

Entity Scene::createEntity() {
  entities.push_back(new Entity(this));
  return *entities.back();
}

Entity *Scene::getEntityPtr(Entity &entity) {
  for(Entity* entityPtr : entities) {
    if(entityPtr->id == entity.id) {
      return entityPtr;
    }
  }
  return nullptr;
}
