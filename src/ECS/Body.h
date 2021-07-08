#ifndef RPG_BODY_H
#define RPG_BODY_H

#include <box2d/box2d.h>
#include <vector>
#include <iostream>
#include <variant>
#include "../Shapes.h"

struct World;

struct Body {
  Body() = default;

  enum struct BodyType {
    STATIC_BODY,
    DYNAMIC_BODY
  };

  BodyType bodyType = BodyType::STATIC_BODY;

  glm::vec2 getPosition();
  glm::vec2 getLinearVelocity();
  float getAngle() const;

  void setLinearVelocity(const glm::vec2& velocity);
  void setPosition(const glm::vec2& position);
  void setSize(const glm::vec2& position);

  void addCollisionShape(Shapes& shape);

  void setType(BodyType bodyType);

private:
    World* world;
    b2BodyDef properties;
    b2Body* body = nullptr;

    std::vector<Shapes> shapes;

    friend struct World;

    explicit Body(BodyType type) {
      bodyType = type;
    }
};


#endif //RPG_BODY_H
