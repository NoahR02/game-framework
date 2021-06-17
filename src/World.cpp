#include "World.h"

World::World() {
  world = new b2World(b2Vec2{gravity.x, gravity.y});
}

[[nodiscard]] glm::vec2 World::pixelsToWorld(glm::vec2 input) const {
  input.x *= pixelsPerMeter;
  input.y *= pixelsPerMeter;
  return input;
}

[[nodiscard]] glm::vec2 World::worldToPixels(glm::vec2 input) const {
  input.x /= pixelsPerMeter;
  input.y /= pixelsPerMeter;
  return input;
}

void World::step(float deltaTime) const {
  world->Step(deltaTime, velocityIterations, positionIterations);
}

void World::createBody(Body& body) const {
  body.body = world->CreateBody(&body.properties);
}

void World::setGravity(const glm::vec2& gravity) {
  this->gravity = gravity;
  world->SetGravity({gravity.x, gravity.y});
}

[[nodiscard]] glm::vec2 World::getGravity() const {
  return gravity;
}