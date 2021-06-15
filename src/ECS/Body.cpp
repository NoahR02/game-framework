#include <glm/vec2.hpp>
#include "Body.h"

glm::vec2 Body::getPosition() {
  auto position = body->GetPosition();
  return glm::vec2(position.x*scaleX, position.y*scaleY);
}

void Body::setLinearVelocity(const glm::vec2& velocity) {
  body->SetLinearVelocity({velocity.x, velocity.y});
}

glm::vec2 Body::getLinearVelocity() {
  auto velocity = body->GetLinearVelocity();
  return {velocity.x, velocity.y};
}

void Body::setPosition(const glm::vec2& position) {
  body->SetTransform({position.x/scaleX, position.y/scaleY}, body->GetAngle());
}

void Body::setScaleX(float scaleX) {
  if(scaleX != 0)
    this->scaleX = scaleX;
}

void Body::setScaleY(float scaleY) {
  if(scaleY != 0)
    this->scaleY = scaleY;
}

float Body::getScaleX() const {
  return scaleX;
}
float Body::getScaleY() const {
  return scaleY;
}