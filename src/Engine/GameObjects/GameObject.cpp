#include <glad/glad.h>
#include <iostream>
#include <chrono>
#include "GameObject.h"

GameObject::GameObject(Texture* texture, int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
  vbo = new VertexBuffer();
  ebo = new ElementBuffer();
  this->texture = texture;

  vbo->bind();
  ebo->bind();
  texture->bind();

  vertices = {
    // pos                                              //tex
    (float)x + width, (float)y, 0.0f,                        1.0f, 1.0f,              // top right
    (float)x, (float)y, 0.0f,                                0.0f, 1.0f,              // top left
    (float)x, (float)y - height, 0.0f,                       0.0f, 0.0f,              // bottom left
    (float)x + width, (float)y - height, 0.0f,                1.0f, 0.0f,              // bottom right
  };

  vbo->buffer(sizeof(float) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);
  ebo->buffer(sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
}

void GameObject::move() {
  vbo->bind();

  vertices = {
    // pos                                              //tex
    (float)x + width, (float)y, 0.0f,                        1.0f, 1.0f,              // top right
    (float)x, (float)y, 0.0f,                                0.0f, 1.0f,              // top left
    (float)x, (float)y - height, 0.0f,                       0.0f, 0.0f,              // bottom left
    (float)x + width, (float)y - height, 0.0f,                1.0f, 0.0f,              // bottom right
  };

  vbo->buffer(sizeof(float) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);
}

GameObject::~GameObject() {
  auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::cout << "Deleting Game Object At: " << std::ctime(&time) << std::endl;

  delete vbo;
  delete ebo;
  delete program;
}

void GameObject::setProgram(const char *vertexShaderSource, const char *fragmentShaderSource) {
  Shader* vertexShader = new Shader(GL_VERTEX_SHADER, vertexShaderSource);
  Shader* fragmentShader = new Shader(GL_FRAGMENT_SHADER, fragmentShaderSource);

  program = new Program({*vertexShader, *fragmentShader});

  delete vertexShader;
  delete fragmentShader;
}
