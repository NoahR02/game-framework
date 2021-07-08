#ifndef RPG_WORLD_H
#define RPG_WORLD_H


#include <box2d/box2d.h>
#include <glm/vec2.hpp>
#include "ECS/Body.h"

struct World {

  int32 velocityIterations = 8;
  int32 positionIterations = 3;
  float pixelsPerMeter = 16;

  [[nodiscard]] glm::vec2 pixelsToWorld(const glm::vec2& input) {
    return {input.x / pixelsPerMeter, input.y / pixelsPerMeter};
  }

  [[nodiscard]] glm::vec2 worldToPixels(const glm::vec2& input) {
    return {input.x * pixelsPerMeter, input.y * pixelsPerMeter};
  }

  World();

  void step(float deltaTime) const;

  void createBody(Body& body);

  void setGravity(const glm::vec2& gravity);
  [[nodiscard]] glm::vec2 getGravity() const;

  void setDebugDraw(b2Draw& b2Draw);
  void drawDebugData();

private:
  b2World* world;
  glm::vec2 gravity {0.0f, 100.0f};

};

#endif
