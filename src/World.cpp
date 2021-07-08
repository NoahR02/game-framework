#include "World.h"

World::World() {
  world = new b2World(b2Vec2{gravity.x, gravity.y});
}

void World::step(float deltaTime) const {
  world->Step(deltaTime, velocityIterations, positionIterations);
}

void World::createBody(Body& body) {
  body.world = this;
  body.body = world->CreateBody(&body.properties);
}

void World::setGravity(const glm::vec2& gravity) {
  this->gravity = gravity;
  world->SetGravity({gravity.x, gravity.y});
}

[[nodiscard]] glm::vec2 World::getGravity() const {
  return gravity;
}

void World::setDebugDraw(b2Draw& b2Draw) {
  world->SetDebugDraw(&b2Draw);
}

void World::drawDebugData() {
  world->DebugDraw();
}
