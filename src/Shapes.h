#ifndef RPG_SHAPES_H
#define RPG_SHAPES_H

#include <box2d/box2d.h>
#include <variant>

enum struct CollisionShapeType {
  POLYGON_SHAPE,
  CIRCLE_SHAPE,
  EDGE_SHAPE,
  CHAIN_SHAPE
};

struct PolygonShape {
  struct World* world;

  b2PolygonShape polygon;

  void set(const std::vector<glm::vec2>& vertices);

  void setAsBox(glm::vec2 size);

};

struct CircleShape {
  b2CircleShape circle;

  struct World* world;

  void set(const glm::vec2& position, float radius);

};

struct EdgeShape {
  struct World* world;
};

struct ChainShape {
  struct World* world;
};

using Shapes = std::variant<PolygonShape, CircleShape, EdgeShape, ChainShape>;

#endif
