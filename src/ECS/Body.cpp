#include <glm/vec2.hpp>
#include <glm/trigonometric.hpp>
#include "Body.h"

#include "../src/World.h"

glm::vec2 Body::getPosition() {
  auto position = body->GetPosition();
  return glm::vec2(world->worldToPixels({position.x, position.y}));
}

void Body::setLinearVelocity(const glm::vec2& velocity) {
  body->SetLinearVelocity({velocity.x, velocity.y});
}

glm::vec2 Body::getLinearVelocity() {
  auto velocity = body->GetLinearVelocity();
  return {velocity.x, velocity.y};
}

void Body::setPosition(const glm::vec2& position) {
  auto tmp = world->pixelsToWorld(position);
  body->SetTransform(b2Vec2{tmp.x, tmp.y}, body->GetAngle());
}

void Body::setSize(const glm::vec2& position) {
}

void Body::addCollisionShape(Shapes& shape) {
  if(auto tmpShape = std::get_if<PolygonShape>(&shape)) {
    tmpShape->world = world;
    body->CreateFixture(&tmpShape->polygon, 1.0f);
  } else if(auto tmpShape = std::get_if<CircleShape>(&shape)) {
    tmpShape->world = world;
    body->CreateFixture(&tmpShape->circle, 1.0f);
  }  else if(auto tmpShape = std::get_if<EdgeShape>(&shape)) {
    tmpShape->world = world;
  }  else if(auto tmpShape = std::get_if<ChainShape>(&shape)) {
    tmpShape->world = world;
  }

  shapes.push_back(shape);
}

void Body::setType(BodyType bodyType) {
  this->bodyType = bodyType;
  if(body) {
    if(bodyType == BodyType::DYNAMIC_BODY)
      body->SetType(b2_dynamicBody);
    else if(bodyType == BodyType::STATIC_BODY)
      body->SetType(b2_staticBody);
  }
}

float Body::getAngle() const {
  return glm::degrees(body->GetAngle());
}
