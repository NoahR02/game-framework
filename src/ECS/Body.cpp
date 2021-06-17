#include <glm/vec2.hpp>
#include "Body.h"

glm::vec2 Body::getPosition() {
  auto position = body->GetPosition();
  return glm::vec2(position.x*16, position.y*16);
}

void Body::setLinearVelocity(const glm::vec2& velocity) {
  body->SetLinearVelocity({velocity.x, velocity.y});
}

glm::vec2 Body::getLinearVelocity() {
  auto velocity = body->GetLinearVelocity();
  return {velocity.x, velocity.y};
}

void Body::setPosition(const glm::vec2& position) {
  body->SetTransform({position.x/16, position.y/16}, body->GetAngle());
}

void Body::setSize(const glm::vec2& position) {

}