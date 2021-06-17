#ifndef RPG_BODY_H
#define RPG_BODY_H


#include <box2d/box2d.h>
#include <vector>
#include <iostream>
#include <variant>

enum struct CollisionShapeType {
  POLYGON_SHAPE,
  CIRCLE_SHAPE,
  EDGE_SHAPE,
  CHAIN_SHAPE
};

struct PolygonShape {

  float width;
  float height;

  b2PolygonShape polygon;

  void set(const std::vector<glm::vec2>& vertices) {
    polygon.Set(reinterpret_cast<const b2Vec2*>(vertices.data()), vertices.size());
  }

  void setAsBox(float width, float height) {
    polygon.SetAsBox(width, height);
  }

};

struct CircleShape {

  b2CircleShape circle;

  void set(const glm::vec2& position, float radius) {
    circle.m_p = {position.x, position.y};
    circle.m_radius = radius;
  }

};

struct EdgeShape {

};

struct ChainShape {

};


struct Body {

  Body() = default;

  enum struct BodyType {
    STATIC_BODY,
    DYNAMIC_BODY
  };

  BodyType bodyType = BodyType::STATIC_BODY;

  glm::vec2 getPosition();
  glm::vec2 getLinearVelocity();

  void setInitPosition(const glm::vec2& position) {
    properties.position.Set(position.x, position.y);
  }

  void setLinearVelocity(const glm::vec2& velocity);
  void setPosition(const glm::vec2& position);
  void setSize(const glm::vec2& position);

  void addCollisionShape(
      std::variant<
          PolygonShape,
          CircleShape,
          EdgeShape,
          ChainShape
      >& shape) {
    b2PolygonShape shape1;
    shape1.SetAsBox(1, 1);
    if(auto tmpShape = std::get_if<PolygonShape>(&shape)) {
      tmpShape->setAsBox(4, 1);
      body->CreateFixture(&shape1, 1.0f);
    } else {
      std::printf("Not working...");
    }
   // if(const auto& tmpShape = std::get_if<CircleShape>(&shape)) body->CreateFixture(&tmpShape->circle, 1.0f);
    
    shapes.push_back(shape);
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

private:
    b2BodyDef properties;
    b2Body* body = nullptr;

    std::vector<std::variant<
        PolygonShape,
        CircleShape,
        EdgeShape,
        ChainShape
    >> shapes;

    friend struct World;

    explicit Body(BodyType type) {
      bodyType = type;
    }

  };


#endif //RPG_BODY_H
