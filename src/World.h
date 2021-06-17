#ifndef RPG_WORLD_H
#define RPG_WORLD_H


#include <box2d/box2d.h>
#include <glm/vec2.hpp>
#include "ECS/Body.h"

struct World {

  float pixelsPerMeter = 16.0f;
  int32 velocityIterations = 8;
  int32 positionIterations = 3;

  World();

  [[nodiscard]] glm::vec2 pixelsToWorld(glm::vec2 input) const;
  [[nodiscard]] glm::vec2 worldToPixels(glm::vec2 input) const;

  void step(float deltaTime) const;

  void createBody(Body& body) const;

  void setGravity(const glm::vec2& gravity);
  [[nodiscard]] glm::vec2 getGravity() const;

private:
  b2World* world;
  glm::vec2 gravity {0.0f, 100.0f};

};

#endif
