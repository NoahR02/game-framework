#include <glm/vec2.hpp>
#include <vector>
#include "Shapes.h"
#include "World.h"

void PolygonShape::set(World& world, const std::vector<glm::vec2>& vertices) {
  std::vector<glm::vec2> transformedVertices(vertices.size());
  for(const auto& vertex : vertices) {
    transformedVertices.push_back(world.pixelsToWorld(vertex));
  }
  polygon.Set(reinterpret_cast<const b2Vec2*>(vertices.data()), vertices.size());
}

void PolygonShape::setAsBox(World& world, glm::vec2 size) {
  size = world.pixelsToWorld(size);
  //polygon.SetAsBox(size.x / 2, size.y / 2);
  //polygon.SetAsBox(size.x / 2, size.y / 2, {size.x / 2, size.y / 2}, 0.0f);

  std::vector<b2Vec2> points = {
    b2Vec2(size.x, size.y),
    b2Vec2(size.x, 0),
    b2Vec2(0, 0),
    b2Vec2(0, size.y),
  };

  polygon.Set(&points.front(), points.size());
}

void CircleShape::set(World& world, const glm::vec2& position, float radius) {
  circle.m_p = {position.x, position.y};
  circle.m_radius = radius;
}