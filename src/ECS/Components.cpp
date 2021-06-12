#include "Components.h"

Components::StaticRenderGroup::StaticRenderGroup(const std::string& texturePath) {
  vao = std::make_unique<VertexArray>();
  vao->bind();

  vbo = std::make_unique<VertexBuffer>();
  vbo->bind();

  ebo = std::make_unique<ElementBuffer>();
  ebo->bind();

  shaderProgram = std::make_unique<ShaderProgram>("shaders/defaultVertex.vert", "shaders/defaultFragment.frag");

  texture = std::make_unique<Texture>(texturePath);
  texture->bind();
}



Components::TileMap::TileMap(int tileWidth, int tileHeight): tileWidth(tileHeight), tileHeight(tileHeight) {
}

Components::Camera::Camera(float width, float height) : width(width), height(height) {
  projection = glm::ortho(0.0f, width, height, 0.0f);
  view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  mvp = projection * view;
}

void Components::Camera::onNotify(Window &window, Event event) {
  setWidth(window.getWidth());
  setHeight(window.getHeight());
}
