#ifndef RPG_BODY_H
#define RPG_BODY_H


#include <box2d/box2d.h>
#include <vector>
#include <iostream>

struct Body {

  Body() = default;

  enum struct BodyType {
    STATIC_BODY,
    DYNAMIC_BODY
  };

  BodyType bodyType = BodyType::DYNAMIC_BODY;

  glm::vec2 getPosition();
  glm::vec2 getLinearVelocity();

  void setInitPosition(const glm::vec2& position) {
    properties.position.Set(position.x/scaleX, position.y/scaleY);
  }

  void setLinearVelocity(const glm::vec2& velocity);
  void setPosition(const glm::vec2& position);

  void setShape(const glm::vec2& size) {
    shape.SetAsBox(size.x/scaleX/2, size.y/scaleY/2);
  }

  void setType(BodyType bodyType) {
    this->bodyType = bodyType;
    if(body) {
      if(bodyType == BodyType::DYNAMIC_BODY)
        body->SetType(b2_dynamicBody);
      else if(bodyType == BodyType::STATIC_BODY)
        body->SetType(b2_staticBody);
    }
  }

  void setScaleX(float scaleX);

  void setScaleY(float scaleY);

  float getScaleX() const;
  float getScaleY() const;

private:
    b2BodyDef properties;
    b2Body* body = nullptr;
    b2PolygonShape shape;

    float scaleX = 1;
    float scaleY = 1;

    friend struct World;

    explicit Body(BodyType type) {
      bodyType = type;
    }

  };


#endif //RPG_BODY_H
