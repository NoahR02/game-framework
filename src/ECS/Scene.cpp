#include "Scene.h"

#include "Entity.h"

Entity Scene::createEntity() {
  return Entity(this);
}