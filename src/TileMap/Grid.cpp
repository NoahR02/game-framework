#include "Grid.h"

Grid::Grid(const int& width, const int& height, int tileWidth, int tileHeight) {
  shaderProgram = std::make_unique<ShaderProgram>("shaders/line.vert", "shaders/line.frag");
  vao = std::make_unique<VertexArray>();
  pointsVBO = std::make_unique<VertexBuffer>();

  calculateGridSize(width, height, tileWidth, tileHeight);
}

void Grid::calculateGridSize(const int& width, const int height, int tileWidth, int tileHeight) {
  points.clear();

  for (int i = 0; i < height; i+= tileHeight) {
    points.insert(points.end(), {
      0, static_cast<float>(i),
      static_cast<float>(0 + width), static_cast<float>(i)
    });
  }

  for (int i = 0; i < width; i+= tileWidth) {
    points.insert(points.end(), { static_cast<float>(i), 0, static_cast<float>(i), static_cast<float>(height) });
  }

  vao->bind();
  pointsVBO->bind();
  pointsVBO->fillBuffer(points);

  vao->enableAttribute(0);
  vao->describeAttributeLayout(0, 2, GL_FLOAT, false, 0, 0);
}

void Grid::draw(const Camera& camera) {
  shaderProgram->bind();

  shaderProgram->setUniformMatrix4fv("uMVP", 1, false, &camera.mvp[0][0]);
  shaderProgram->setUniform4f("uColor", 0, 0, 0, .1);
  glLineWidth(2);
  vao->bind();
  pointsVBO->bind();
  glDrawArrays(GL_LINES, 0, points.size());
}